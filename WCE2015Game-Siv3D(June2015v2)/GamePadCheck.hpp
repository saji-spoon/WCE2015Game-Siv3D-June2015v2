#pragma once
#include<Siv3D.hpp>

namespace shimi
{
class GamepadCheck
{
public:

	static GamepadCheck* I()
	{
		static GamepadCheck instance;
		return &instance;
	}

	GamepadCheck(const GamepadCheck& rhs) = delete;

	GamepadCheck& operator=(const GamepadCheck& rhs) = delete;

private:

	GamepadCheck()
	{
	}

	double preX = 0;
	double preY = 0;

public:

	bool leftClicked()
	{
		return preX != -1 && Gamepad(0).x == -1;
	}

	bool rightClicked()
	{
		return preX != 1 && Gamepad(0).x == 1;
	}

	bool upClicked()
	{
		return preY != 1 && Gamepad(0).y == 1;
	}

	bool downClicked()
	{
		return preY != -1 && Gamepad(0).y == -1;
	}

	void update()
	{
		preX = Gamepad(0).x;
		preY = Gamepad(0).y;
	}

};

};