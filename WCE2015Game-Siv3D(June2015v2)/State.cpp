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

	//ƒQ[ƒ€‚ÌUpdate‚Í‚¹‚¸‚Éƒƒjƒ…[‚Ìupdate‚ÆƒQ[ƒ€Eƒƒjƒ…[‚Ì•`‰æ‚Ì‚İ

	gb->m_menu.update();
}