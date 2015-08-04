#pragma once
#include<Siv3D.hpp>
#include"MyVehicle.hpp"
#include"Camera.hpp"
#include"Ballet.hpp"
#include "Enemy.hpp"
#include"BalletManager.hpp"
#include"EnemyManager.hpp"

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

	std::vector<Obstacle> m_obstacles;

	D2Camera m_camera;

	GameBase();

	void update();

	inline Vec2 getMyVehiclePos()
	{
		return m_mv.m_pos;
	}

	void updateCamera(const Vec2& cPos)
	{
		m_camera.m_pos = cPos;
	}

	void collisionPlayerWithEnemy()const;

	void draw()const;


};

}