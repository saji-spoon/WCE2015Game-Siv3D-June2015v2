#pragma once
#include<Siv3D.hpp>
#include"MyVehicle.hpp"
#include"State.hpp"


namespace shimi
{
enum class TitleSelect
{
	Executing,
	NewGame,
	Continue
};


class Title
{
public:
	Texture m_BackTex = Texture(L"Resource/Paper2.png");
	Texture m_TitleTex = Texture(L"Resource/GUI/Title.png");
	Texture m_NewGameTex = Texture(L"Resource/GUI/NewGame.png");
	Texture m_ContinueTex = Texture(L"Resource/GUI/Continue.png"); 
	Texture m_CursorTex = Texture(L"Resource/GUI/Cursor.png");

	Font m_verFont;

	int m_select = 0;

	int m_menuNum = 2;

	TitleSelect m_titleSelect = TitleSelect::Executing;

	Title();

	void draw()const;
	void update();

	TitleSelect getSelect()const
	{
		return m_titleSelect;
	}
};

}