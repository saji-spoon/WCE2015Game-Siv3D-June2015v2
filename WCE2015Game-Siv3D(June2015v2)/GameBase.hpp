#pragma once
#include<Siv3D.hpp>
#include"MyVehicle.hpp"
#include"Camera.hpp"
#include"Ballet.hpp"
#include"BalletManager.hpp"

namespace shimi
{

class GameBase
{
private:
public:

	Image m_image = Image(Window::Size(), Palette::White);

	DynamicTexture m_dTex = DynamicTexture(m_image);

	//myBalletManager;
	BalletManager m_myBM;

	MyVehicle mv = MyVehicle(this);

	D2Camera m_camera;

	GameBase() :m_camera(mv.m_pos), m_myBM(this)
	{
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