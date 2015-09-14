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

	//コンストラクタ
	Enemy(EnemyManager* manager, const Vec2& pos, const shimi::MyAnime& anime, ShimiColors sColor, const Optional<ItemRecord>& ir);

	//敵の動きの実装
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

	//コンストラクタ
	CoEnemy(int id, const std::shared_ptr<Enemy>& bp) :m_id(id), co(move), m_enemy(bp)
	{
	}


	/*
	//コピーコンストラクタを隠してcopyを明示的に使わせる場合
	CoEnemy(const CoEnemy& rhs) = delete;
	CoEnemy& operator =(const CoEnemy & rhs) = delete;
	void copy(const CoEnemy& rhs)
	{
		m_id = rhs.m_id;

		m_enemy = m_enemy->clone();

		co = boco::coroutine<Enemy*>::push_type(move);

		LOG_DEBUG(L"CopyFunc");
	}*/
	

	
	
	//ユーザー定義コピーコンストラクタ
	CoEnemy(const CoEnemy& rhs) :m_id(rhs.m_id), co(move), m_enemy(rhs.m_enemy->clone())
	{
		LOG_DEBUG(L"CopyCtor");
	}


	///ユーザー定義コピー代入演算子
	CoEnemy& operator =(const CoEnemy & rhs)
	{
		m_id = rhs.m_id;

		m_enemy = m_enemy->clone();

		co = boco::coroutine<Enemy*>::push_type(move);

		LOG_DEBUG(L"Copy=");
	}
	
	

	///ユーザー定義ムーブ代入演算子
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

		///ユーザー定義ムーブコンストラクタ
		///ムーブ代入演算子を用いるようになったので、ムーブコンストラクタ呼び出し時にはMove= MoveCtorと表記される
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

	//敵の動きの実装
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