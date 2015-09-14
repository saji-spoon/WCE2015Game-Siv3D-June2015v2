#pragma once
#include<Siv3D.hpp>
#include<boost/coroutine/all.hpp>
#include"MyAnime.hpp"
#include"ShimiColors.hpp"
#include"ItemDatabase.hpp"
#include"Config.hpp"
#include"Camera.hpp"



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

	bool m_isDead;

	Enemy(){}

	//�R���X�g���N�^
	Enemy(EnemyManager* manager, const Vec2& pos, const shimi::MyAnime& anime, ShimiColors sColor, const Optional<ItemRecord>& ir);

	//�G�̓����̎���
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

class CoEnemy
{
public:

	std::shared_ptr<Enemy> m_enemy;

	boco::coroutine<Enemy*>::push_type co;
	//ID@EnemyDB
	int m_id = -1;

	//�R���X�g���N�^
	CoEnemy(int id, const std::shared_ptr<Enemy>& bp) :m_id(id), co(move), m_enemy(bp)
	{
	}


	/*
	//�R�s�[�R���X�g���N�^���B����copy�𖾎��I�Ɏg�킹��ꍇ
	CoEnemy(const CoEnemy& rhs) = delete;
	CoEnemy& operator =(const CoEnemy & rhs) = delete;
	void copy(const CoEnemy& rhs)
	{
		m_id = rhs.m_id;

		m_enemy = m_enemy->clone();

		co = boco::coroutine<Enemy*>::push_type(move);

		LOG_DEBUG(L"CopyFunc");
	}*/
	

	
	
	//���[�U�[��`�R�s�[�R���X�g���N�^
	CoEnemy(const CoEnemy& rhs) :m_id(rhs.m_id), co(move), m_enemy(rhs.m_enemy->clone())
	{
		LOG_DEBUG(L"CopyCtor");
	}


	///���[�U�[��`�R�s�[������Z�q
	CoEnemy& operator =(const CoEnemy & rhs)
	{
		m_id = rhs.m_id;

		m_enemy = m_enemy->clone();

		co = boco::coroutine<Enemy*>::push_type(move);

		LOG_DEBUG(L"Copy=");
	}
	
	

	///���[�U�[��`���[�u������Z�q
	CoEnemy& operator =(CoEnemy && rhs) _NOEXCEPT
	{
		if (&rhs != this)
		{
			m_id = rhs.m_id;
			//m_enemy = std::move(rhs.m_enemy);
			m_enemy = rhs.m_enemy;
			rhs.m_enemy.reset();
			co = std::move(rhs.co);
			LOG_DEBUG(L"shared_ptr:", m_enemy.use_count());
		}

		LOG_DEBUG(L"Move=");

		return *this;
	}

		///���[�U�[��`���[�u�R���X�g���N�^
		///���[�u������Z�q��p����悤�ɂȂ����̂ŁA���[�u�R���X�g���N�^�Ăяo�����ɂ�Move= MoveCtor�ƕ\�L�����
		CoEnemy(CoEnemy&& rhs) _NOEXCEPT
	{
		*this = std::move(rhs);

		LOG_DEBUG(L"MoveCtor");
	}

	~CoEnemy() = default;

	static void move(boco::coroutine<Enemy*>::pull_type& yield)
	{
		Enemy* B = yield.get();

		B->moveImpl(yield);
	}

	void draw()const
	{
		m_enemy->draw();
	}

	void update()
	{
		m_enemy->update();

		co(m_enemy.get());
	}
};


class BasicEnemy : public Enemy
{
public:

	BasicEnemy(){}
	BasicEnemy(EnemyManager* manager, const Vec2& pos, const shimi::MyAnime& anime, ShimiColors sColor, const Optional<ItemRecord>& ir = none) :Enemy(manager, pos, anime, sColor, ir)
	{}

	//�G�̓����̎���
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