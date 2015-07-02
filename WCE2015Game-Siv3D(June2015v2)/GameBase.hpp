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

	Image m_image = Image(Window::Size(), Palette::White);

	DynamicTexture m_dTex = DynamicTexture(m_image);

	//myBalletManager;
	BalletManager m_myBM = BalletManager(this);
	//EnemyManager
	EnemyManager m_EM = EnemyManager(this);

	MyVehicle mv = MyVehicle(this);

	D2Camera m_camera;

	GameBase() :m_camera(mv.m_pos)
	{
		/*for prototype*/

		m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy{ &m_EM, {120.0, 300.0} }));

	}

	void update();

	inline Vec2 getMyVehiclePos()
	{
		return mv.m_pos;
	}

	void updateCamera(const Vec2& cPos)
	{
		m_camera.m_pos = cPos;
	}

	void draw()const;


};

}