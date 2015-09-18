#include"Menu.hpp"
#include"GameBase.hpp"

using namespace shimi;

void Menu::update()
{
	//SƒL[‚ð‰Ÿ‚µ‚½‚ç”²‚¯‚é
	if (Input::KeyS.clicked)
	{
		m_gb->changeState(std::shared_ptr<state::GBState>(new state::MainGame()));
	}
}

void Menu::draw()const
{
	Rect(Window::Size()).draw(Color(0, 0, 0, 230));

}