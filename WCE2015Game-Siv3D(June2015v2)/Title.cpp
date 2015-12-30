#include"Title.hpp"
#include"Config.hpp"

using namespace shimi;

Title::Title()
{
	m_verFont = Font(24, L"02������������", FontStyle::Bold);
	//m_verFont.changeOutlineStyle(TextOutlineStyle(Color(185,185,185), Palette::White, 2.0));
}

void Title::update()
{
	//���肵���瑀��Ȃǂ͎󂯕t���Ȃ�
	if (m_titleSelect != TitleSelect::Executing) return;

	if (ConfigParam::KEY_A_CLICKED())
	{
		switch (m_select)
		{
		case 0:
			SoundAsset(L"Start").play();
			m_titleSelect = TitleSelect::NewGame;
			return;
		case 1:
			//���̓Z�[�u�@�\�Ȃ��̂���Continue�I��s��
			SoundAsset(L"Start").play();
			m_titleSelect = TitleSelect::Continue;
			return;
		default:
			break;
		}
	}

	//���̑I���͏㉺�L�[
	const int selectAdd = ConfigParam::KEY_UP_CLICKED() ? -1 : (ConfigParam::KEY_DOWN_CLICKED() ? 1 : 0);

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
	m_verFont.draw(L"v.0.94", Vec2(1160, 737), Color(200, 200, 200));

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