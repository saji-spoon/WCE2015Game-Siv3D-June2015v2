# include <Siv3D.hpp>
#include<algorithm>
#include"Camera.hpp"
#include"MyVehicle.hpp"
#include"GameBase.hpp"
#include"Resource.hpp"

using namespace shimi;

void Main()
{
	ResourceRegister();

	Window::Resize(1280, 800);

	GameBase gb;

	while (System::Update())
	{

		gb.draw();

		gb.update();

		if (Input::MouseL.pressed)
		{

		}
	}
}
