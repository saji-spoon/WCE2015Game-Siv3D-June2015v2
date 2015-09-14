#pragma once
#include<Siv3D.hpp>
#include"ShimiColors.hpp"
#include"Camera.hpp"

namespace shimi
{
class GameBase;

class Shot
{
public:
	GameBase* m_gb;

	ShimiColors m_color;

	//インターバル管理用count
	int m_count;

	//インターバル設定値
	int m_interval;

	Shot() 
	{}

	Shot(GameBase* gb, int interval) :m_gb(gb), m_interval(interval)
	{}

	int getLevel()const;

	virtual void draw()const = 0;

	//ショット選択時のフレーム描画
	virtual void drawFrame()const = 0;

	virtual void shot() = 0;

	virtual void update() { if (m_count > 0) --m_count; };

};

class RedShot1 : public Shot
{
public:
	Texture m_tex = Texture(L"Resource/Hero/red-1.png");

	RedShot1(GameBase* gb) :Shot(gb, 30)
	{}

	void draw()const override;

	void drawFrame()const override;

	void shot()override;
};


class BlueShot1 : public Shot
{
public:
	Texture m_tex = Texture(L"Resource/Hero/blue-1.png");

	BlueShot1(GameBase* gb) :Shot(gb, 30)
	{}

	void draw()const override;

	void drawFrame()const override;

	void shot()override;
};


class WhiteShot : public Shot
{
public:

	WhiteShot(GameBase* gb) :Shot(gb, 75) 
	{}

	void draw()const override
	{
	}

	void drawFrame()const override
	{
	}

	void shot()override;

};


}