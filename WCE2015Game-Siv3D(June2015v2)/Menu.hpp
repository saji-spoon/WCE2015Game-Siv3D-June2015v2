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
	MyVehicle m_mvData;

	GameBase* m_gb;

	int m_select = 0;

	Menu(GameBase* gb, const MyVehicle& mvData);

	void draw()const;
	void update();
};

}