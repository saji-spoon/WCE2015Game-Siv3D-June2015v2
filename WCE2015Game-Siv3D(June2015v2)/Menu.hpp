#pragma once
#include<Siv3D.hpp>
#include"MyVehicle.hpp"
#include"State.hpp"

namespace shimi
{
class GameBase;

class Menu
{
public:
	MyVehicle::ShotManager m_shotData;

	GameBase* m_gb;

	Menu(GameBase* gb, const MyVehicle::ShotManager& shotData) :m_gb(gb), m_shotData(shotData)
	{
	}

	void draw()const;
	void update();
};

}