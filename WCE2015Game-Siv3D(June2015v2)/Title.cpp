#include"Title.hpp"
#include"Config.hpp"

using namespace shimi;

Title::Title()
{
	m_verFont = Font(24, L"02うつくし明朝体", FontStyle::Bold);
	//m_verFont.changeOutlineStyle(TextOutlineStyle(Color(185,185,185), Palette::White, 2.0));
}

void Title::update()
{
	//決定したら操作などは受け付けない
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
			//今はセーブ機能なしのためContinue選択不可
			SoundAsset(L"Start").play();
			m_titleSelect = TitleSelect::Continue;
			return;
		default:
			break;
		}
	}

	//欄の選択は上下キー
	const int selectAdd = ConfigParam::KEY_UP_CLICKED() ? -1 : (ConfigParam::KEY_DOWN_CLICKED() ? 1 : 0);

	if (selectAdd != 0) SoundAsset(L"Select").playMulti();

	//装備可能数に足りない欄は選択できない
	if (selectAdd != 0) m_select = (m_select + selectAdd + m_menuNum) % (m_menuNum);

}

void Title::draw()const
{
	m_BackTex.map(1280, 800).draw(Alpha(70));
	m_TitleTex.draw();
	m_NewGameTex.draw();
	m_ContinueTex.draw();
	m_verFont.draw(L"v.0.94", Vec2(1160, 737), Color(200, 200, 200));

	//選択UI描画
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