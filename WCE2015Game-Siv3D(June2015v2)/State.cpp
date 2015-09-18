#include"State.hpp"
#include"GameBase.hpp"

using namespace shimi;

void state::MainGame::execute(GameBase* gb)
{
	gb->draw();

	gb->mainGameUpdate();
}

void state::Menu::execute(GameBase* gb)
{
	gb->draw();

	gb->m_menu.draw();

	//ゲームのUpdateはせずにメニューのupdateとゲーム・メニューの描画のみ

	gb->m_menu.update();
}