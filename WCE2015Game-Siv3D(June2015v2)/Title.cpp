#include"Title.hpp"

using namespace shimi;

Title::Title()
{

}

void Title::update()
{
	//���肵���瑀��Ȃǂ͎󂯕t���Ȃ�
	if (m_titleSelect != TitleSelect::Executing) return;

	//S�L�[���������甲����
	if (Input::KeyZ.clicked)
	{
		switch (m_select)
		{
		case 0:
			SoundAsset(L"Start").play();
			m_titleSelect = TitleSelect::NewGame;
			return;
		case 1:
			//���̓Z�[�u�@�\�Ȃ��̂���Continue�I��s��
			//m_titleSelect = TitleSelect::Continue;
			return;
		default:
			break;
		}
	}

	//���̑I���͏㉺�L�[
	const int selectAdd = Input::KeyUp.clicked ? 1 : (Input::KeyDown.clicked ? -1 : 0);

	if (selectAdd != 0) SoundAsset(L"Select").playMulti();

	//�����\���ɑ���Ȃ����͑I���ł��Ȃ�
	if (selectAdd != 0) m_select = (m_select + selectAdd + m_menuNum) % (m_menuNum);

}

void Title::draw()const
{
	m_BackTex.map(1280, 800).draw(Alpha(70));
	m_TitleTex.draw();
	m_NewGameTex.draw();
	m_ContinueTex.draw();

	//�I��UI�`��
	switch (m_select)
	{
	case 0:
		m_CursorTex.drawAt(Vec2(482, 496));
		return;
	case 1:
		m_CursorTex.drawAt(Vec2(482, 578));
		return;
	default:
		break;
	}
}