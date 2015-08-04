# include <Siv3D.hpp>
#include<algorithm>
#include"Camera.hpp"
#include"MyVehicle.hpp"
#include"GameBase.hpp"
#include"MyResource.hpp"

using namespace shimi;

void Main()
{
	ResourceRegister();

	Window::Resize(1280, 800);

	GameBase gb;

	Graphics::SetBackground(Palette::White);

	while (System::Update())
	{

		gb.draw();

		gb.update();

		if (Input::MouseL.pressed)
		{

		}
	}
}
