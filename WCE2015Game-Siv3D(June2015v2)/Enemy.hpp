#pragma once
#include<Siv3D.hpp>
#include<boost/coroutine/all.hpp>
#include"MyAnime.hpp"
#include"ShimiColors.hpp"
#include"ItemDatabase.hpp"
#include"Config.hpp"
#include"Camera.hpp"
#include"EnemyShot.hpp"
#include"Effect.hpp"


namespace boco = boost::coroutines;

namespace shimi
{
class EnemyManager;
class GameBase;

class Enemy
{
public:
	shimi::MyAnime m_anime;

	std::shared_ptr<EnemyShot> m_shot;

	Vec2 m_pos;

	EnemyManager* m_manager;

	Optional<int> m_itemID=none;

	ShimiColors m_shimiColor;

	int m_depopCount = 0;

	int m_id = -1;

	bool m_isDead;

	Enemy(){}

	//コンストラクタ
	Enemy(EnemyManager* manager,
		const Vec2& pos,
		const shimi::MyAnime& anime,
		const std::shared_ptr<EnemyShot> enemyShot,
		ShimiColors sColor,
		const Optional<ItemRecord>& ir = none);

	//敵の動きの実装
	virtual void move() = 0;

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

	StopEnemy(){}
	StopEnemy(EnemyManager* manager, const Vec2& pos, const shimi::MyAnime& anime, const std::shared_ptr<EnemyShot> enemyShot, ShimiColors sColor, const Optional<ItemRecord>& ir = none)
		:Enemy(manager, pos, anime, enemyShot, sColor, ir)
	{}

	//敵の動きの実装
	void move()override;

	std::shared_ptr<Enemy> clone()override
	{
		return std::shared_ptr<Enemy>(new StopEnemy(*this));
	}

};

class StraightEnemy : public Enemy
{
public:
	std::vector<Vec2> m_poss;

	double m_speed;

	//現在のスタート地点とゴール地点と進行度
	Vec2 m_start;
	Vec2 m_end;
	double m_progress;

	//渡された地点表の0を初期位置とし、1に向かう
	int m_phase = 1;
	int m_indexDir = 1;

	bool m_rotatable;

	bool m_loop;

	bool m_isFinish = false;

	//速度が0のとき前の向きを保持する
	double m_preDir = 0;

	StraightEnemy(){}
	StraightEnemy(EnemyManager* manager,
		std::initializer_list<Vec2> list,
		double speed,
		const shimi::MyAnime& anime,
		const std::shared_ptr<EnemyShot> enemyShot,
		const ShimiColors& sColor,
		const Optional<ItemRecord>& ir = none,
		bool rotatable = false,
		bool loop = true);

	StraightEnemy(EnemyManager* manager,
		std::vector<Vec2>& poss,
		double speed,
		const shimi::MyAnime& anime,
		const std::shared_ptr<EnemyShot> enemyShot,
		const ShimiColors& sColor,
		const Optional<ItemRecord>& ir = none,
		bool rotatable = false,
		bool loop = true);


	//敵の動きの実装
	void move()override;

	//startとendを設定し、progressをリセット
	void setPath(const Vec2& start, const Vec2& end);

	std::shared_ptr<Enemy> clone()override
	{
		return std::shared_ptr<Enemy>(new StraightEnemy(*this));
	}

	void draw()const override;


};

/*
class LineEnemy : public Enemy
{
public:
	std::vector<std::pair<Vec2, int>> m_poss;

	//渡された地点表の0を初期位置とし、1に向かう
	int m_phase = 1;
	int m_timer = 0;
	int m_indexDir = 1;

	bool m_rotatable;

	bool m_loop;

	//速度が0のとき前の向きを保持する
	double preDir = 0;

	Vec2 m_v;

	LineEnemy(){}
	LineEnemy(EnemyManager* manager,
	const std::vector<std::pair<Vec2, int>>& poss,
	const shimi::MyAnime& anime,
	const std::shared_ptr<EnemyShot> enemyShot,
	const  ShimiColors& sColor,
	const Optional<ItemRecord>& ir = none,
	bool rotatable = false,
	bool loop = true) :
	Enemy(
	manager,
	Vec2(0,0),
	anime,
	enemyShot,
	sColor,
	ir),
	m_rotatable(rotatable),
	m_loop(loop)
	{
		if (!poss.empty())
		{	
			m_pos = m_poss[0].first;
		}
		else
		{
			LOG_ERROR(L"LineEnemy: 地点表がありません");
		}

		if (!ir) return;

		m_itemID = m_manager->m_gb->m_idb.Register(ir.value());
	}

	LineEnemy(EnemyManager* manager,
		const std::vector<Vec2>& poss,
		double speed,
		const shimi::MyAnime& anime,
		const std::shared_ptr<EnemyShot> enemyShot,
		const  ShimiColors& sColor,
		const Optional<ItemRecord>& ir = none,
		bool rotatable = false,
		bool loop = true) :
		Enemy(
		manager,
		Vec2(0, 0),
		anime,
		enemyShot,
		sColor,
		ir),
		m_rotatable(rotatable),
		m_loop(loop)
	{
		if (!poss.empty())
		{
			m_pos = m_poss[0].first;
		}
		else
		{
			LOG_ERROR(L"LineEnemy: 地点表がありません");


		}

		if (!ir) return;

		m_itemID = m_manager->m_gb->m_idb.Register(ir.value());
	}


	//敵の動きの実装
	void move()override;

	void calcNextV();

	void calcNextV(int index);

	std::shared_ptr<Enemy> clone()override
	{
		return std::shared_ptr<Enemy>(new BasicEnemy(*this));
	}

};*/

/*
class AdvanceEnemy : public Enemy
{
public:
	AdvanceEnemy(){}
	AdvanceEnemy(EnemyManager* manager, const Vec2& center, const shimi::MyAnime& anime, ShimiColors sColor, const Optional<ItemRecord>& ir = none) :Enemy(manager, center.movedBy(Circular(40, m_theta)), anime, sColor, ir), m_center(center)
	{}

	double m_theta = 0;
	Vec2 m_center;

	void move()override;

	std::shared_ptr<Enemy> clone()override
	{
		return std::shared_ptr<Enemy>(new AdvanceEnemy(*this));
	}


};
*/

}