#pragma once
#include<Siv3D.hpp>
#include"MyVehicle.hpp"
#include"Camera.hpp"
#include"Ballet.hpp"

namespace shimi
{

class GameBase
{
private:
public:

	Image m_image = Image(Window::Size(), Palette::White);

	DynamicTexture m_dTex = DynamicTexture(m_image);

	std::vector<Ballet> m_ballets;

	MyVehicle mv = MyVehicle(this);

	D2Camera m_camera;

	GameBase() :m_camera(mv.m_pos)
	{
	}

	void update();


	void updateCamera(const Vec2& cPos)
	{
		m_camera.m_pos = cPos;
	}

	void draw()const;


};

}