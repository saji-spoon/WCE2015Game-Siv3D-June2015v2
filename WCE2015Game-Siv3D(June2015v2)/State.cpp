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

	//�Q�[����Update�͂����Ƀ��j���[��update�ƃQ�[���E���j���[�̕`��̂�

	gb->m_menu.update();
}