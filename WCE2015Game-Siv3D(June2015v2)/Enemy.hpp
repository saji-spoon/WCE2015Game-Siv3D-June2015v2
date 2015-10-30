#pragma once
#include<Siv3D.hpp>
#include<boost/coroutine/all.hpp>
#include"MyAnime.hpp"
#include"ShimiColors.hpp"
#include"ItemDatabase.hpp"
#include"Config.hpp"
#include"Camera.hpp"
#include"EnemyShot.hpp"



namespace boco = boost::coroutines;

namespace shimi
{
class EnemyManager;
class GameBase;

class Enemy
{
public:
	shimi::MyAnime m_anime;

	Vec2 m_pos;

	EnemyManager* m_manager;

	Optional<int> m_itemID=none;

	ShimiColors m_shimiColor;

	int m_depopCount = 0;

	int m_id = -1;

	bool m_isDead;

	Enemy(){}

	//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	Enemy(EnemyManager* manager, const Vec2& pos, const shimi::MyAnime& anime, ShimiColors sColor, const Optional<ItemRecord>& ir);

	//“G‚Ì“®‚«‚ÌŽÀ‘•
	virtual void moveImpl(boco::coroutine<Enemy*>::pull_type& yield) = 0;

	virtual void draw()const
	{
		m_anime.drawAt(D2Camera::I()->getDrawPos(m_pos));
	}

	virtual void update();

	virtual inline bool isDead()const
	{
		return m_isDead;
	}

	virtual std::shared_ptr<Enemy> clone() = 0;
};

class StopEnemy : public Enemy
{
public:

	std::shared_ptr<EnemyShot> m_shot;

	StopEnemy(){}
	StopEnemy(EnemyManager* manager, const Vec2& pos, const shimi::MyAnime& anime, const std::shared_ptr<EnemyShot> enemyShot, ShimiColors sColor, const Optional<ItemRecord>& ir = none)
		:Enemy(manager, pos, anime, sColor, ir),
		m_shot(enemyShot)
	{}

	//“G‚Ì“®‚«‚ÌŽÀ‘•
	void moveImpl(boco::coroutine<Enemy*>::pull_type& yield);

	std::shared_ptr<Enemy> clone()override
	{
		return std::shared_ptr<Enemy>(new StopEnemy(*this));
	}

};

class BasicEnemy : public Enemy
{
public:

	BasicEnemy(){}
	BasicEnemy(EnemyManager* manager, const Vec2& pos, const shimi::MyAnime& anime, ShimiColors sColor, const Optional<ItemRecord>& ir = none) :Enemy(manager, pos, anime, sColor, ir)
	{}

	//“G‚Ì“®‚«‚ÌŽÀ‘•
	void moveImpl(boco::coroutine<Enemy*>::pull_type& yield)override
	{
		for (;;)
		{
			up(yield);
			down(yield);
		}


		for (;;)
		{
			yield();
		}
	}

	void up(boco::coroutine<Enemy*>::pull_type& yield)
	{
		for (int i = 0; i<60; ++i)
		{
			m_pos += Vec2(0, -1);
			//yield.get()->pos += yield.get()->v;
			yield();
		}

	}

	void down(boco::coroutine<Enemy*>::pull_type& yield)
	{
		for (int i = 0; i<60; ++i)
		{
			m_pos += Vec2(0, 1);
			//yield.get()->pos += yield.get()->v;
			yield();
		}

	}


	std::shared_ptr<Enemy> clone()override
	{
		return std::shared_ptr<Enemy>(new BasicEnemy(*this));
	}

};

class AdvanceEnemy : public Enemy
{
public:
	AdvanceEnemy(){}
	AdvanceEnemy(EnemyManager* manager, const Vec2& center, const shimi::MyAnime& anime, ShimiColors sColor, const Optional<ItemRecord>& ir = none) :Enemy(manager, center.movedBy(Circular(40, m_theta)), anime, sColor, ir), m_center(center)
	{}

	double m_theta = 0;
	Vec2 m_center;

	virtual void moveImpl(boco::coroutine<Enemy*>::pull_type& yield)override
	{
		for (;;)
		{
			m_pos = m_center.movedBy(Circular(40, m_theta));

			m_theta += 0.05;

			yield();
		}
	}

	std::shared_ptr<Enemy> clone()override
	{
		return std::shared_ptr<Enemy>(new AdvanceEnemy(*this));
	}


};

}