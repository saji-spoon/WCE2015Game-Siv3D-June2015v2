#pragma once
#include<Siv3D.hpp>
#include"Camera.hpp"

namespace shimi
{

class GameBase;

class MyVehicle
{
public:
	Vec2 m_pos = Point(640, 400);

	Vec2 m_v = Circular(3, 0);

	std::vector<Polygon> m_walls;

	Texture m_tex = Texture(L"Maze.png");

	GameBase* m_base;


public:
	MyVehicle(GameBase* base);

	void collisionPlayerWithObject();

	void update()
	{
		collisionPlayerWithObject();
	}

	void draw(const D2Camera& camera)const;


};

}