#include"Title.hpp"

using namespace shimi;

Title::Title()
{

}

void Title::update()
{
	//決定したら操作などは受け付けない
	if (m_titleSelect != TitleSelect::Executing) return;

	//Sキーを押したら抜ける
	if (Input::KeyZ.clicked)
	{
		switch (m_select)
		{
		case 0:
			SoundAsset(L"Start").play();
			m_titleSelect = TitleSelect::NewGame;
			return;
		case 1:
			//今はセーブ機能なしのためContinue選択不可
			//m_titleSelect = TitleSelect::Continue;
			return;
		default:
			break;
		}
	}

	//欄の選択は上下キー
	const int selectAdd = Input::KeyUp.clicked ? 1 : (Input::KeyDown.clicked ? -1 : 0);

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