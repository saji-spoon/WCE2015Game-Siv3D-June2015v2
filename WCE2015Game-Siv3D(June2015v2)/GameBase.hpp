#pragma once
#include<Siv3D.hpp>
#include"MyVehicle.hpp"
#include"Camera.hpp"
#include"Ballet.hpp"
#include "Enemy.hpp"
#include"BalletManager.hpp"
#include"EnemyManager.hpp"
#include"EffectManager.hpp"

namespace shimi
{

class GameBase
{
private:
public:
	Texture m_tex;

	//myBalletManager;
	BalletManager m_myBM = BalletManager(this);
	//EnemyManager
	EnemyManager m_EM = EnemyManager(this);

	MyVehicle m_mv = MyVehicle(this);

	ItemDetabase m_idb;

	std::vector<Obstacle> m_obstacles;

	GameBase();

	void update();

	inline Vec2 getMyVehiclePos()
	{
		return m_mv.m_pos;
	}

	void updateCamera(const Vec2& cPos)
	{
		D2Camera::I()->m_pos = cPos;
	}

	void collisionPlayerWithEnemy()const;

	void collisionEnemyWithBallet();

	void collisionBalletWithObstacle();

	void draw()const;


};

}