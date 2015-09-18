# include <Siv3D.hpp>
#include<algorithm>
#include"MyResource.hpp"
#include"GameBase.hpp"

using namespace shimi;

void Main()
{
	ResourceRegister();

	Window::Resize(1280, 800);

	GameBase gb;

	Graphics::SetBackground(Palette::White);

	while (System::Update())
	{
		gb.update();
	}
}
