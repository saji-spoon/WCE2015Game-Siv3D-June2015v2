#pragma once
#include<Siv3D.hpp>
#include"BalletManager.hpp"
#include"EnemyManager.hpp"
#include"MyVehicle.hpp"
#include"ItemDatabase.hpp"
#include"Obstacle.hpp"
#include"Camera.hpp"
#include"AnimeAsset.hpp"
#include"EffectManager.hpp"
#include"Effect.hpp"
#include"State.hpp"
#include"Menu.hpp"

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

	Menu m_menu;

	std::shared_ptr<state::GBState> m_state;

	GameBase();

	void update()
	{
		m_state->execute(this);
	}

	void mainGameUpdate();

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

	void changeState(const std::shared_ptr<state::GBState>& state);


};

}