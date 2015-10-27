#pragma once
#pragma warning( disable : 4100 )
#include<Siv3D.hpp>
#include"ShimiColors.hpp"
#include"Camera.hpp"
#include"Config.hpp"

namespace shimi
{
class GameBase;

class Shot
{
public:
	GameBase* m_gb;

	Optional<ShimiColors> m_color;

	//インターバル管理用count
	int m_count;

	//インターバル設定値
	int m_interval;

	Shot() 
	{}

	Shot(GameBase* gb, int interval, const Optional<ShimiColors>& sCol) :m_gb(gb), m_interval(interval), m_color(sCol)
	{}

	virtual void draw(const Vec2& pos, const Vec2& v)const = 0;

	//ショット選択時のフレーム描画
	virtual void drawFrame(const Vec2& pos, const Vec2& v)const = 0;

	virtual void shot(const Vec2& pos, const Vec2& v) = 0;

	virtual void update()
	{
		if (m_count > 0) --m_count; 
		texUpdate();
	};

	virtual void texUpdate() = 0;

};

class RedShot1 : public Shot
{
public:
	Texture m_tex = Texture(L"Resource/Hero/Equip/red-1.png");
	Texture m_frameTex = Texture(L"Resource/Hero/Equip/FrameLine/redline_1.png");

	RedShot1(GameBase* gb) :Shot(gb, 30, ShimiColors::Red)
	{}
	
	void draw(const Vec2& pos, const Vec2& v)const override;
	
	void  drawFrame(const Vec2& pos, const Vec2& v)const override;

	void shot(const Vec2& pos, const Vec2& v)override;

	void texUpdate()override{}
};

class BlueShot1 : public Shot
{
public:
	Texture m_tex = Texture(L"Resource/Hero//Equip/blue-1.png");
	Texture m_frameTex = Texture(L"Resource/Hero//Equip/FrameLine/blueline_1.png");

	BlueShot1(GameBase* gb) :Shot(gb, 30, ShimiColors::Blue)
	{}

	void draw(const Vec2& pos, const Vec2& v)const override;

	void  drawFrame(const Vec2& pos, const Vec2& v)const override;

	void shot(const Vec2& pos, const Vec2& v)override;

	void texUpdate()override{}
};

class GreenShot1 : public Shot
{
public:
	Texture m_tex = Texture(L"Resource/Hero//Equip/green-1.png");
	Texture m_frameTex = Texture(L"Resource/Hero//Equip/FrameLine/greenline_1.png");

	int m_state = 0;
	int m_stateTimer = 0;

	//レーザー用Line
	Line m_beam;

	GreenShot1(GameBase* gb);

	void draw(const Vec2& pos, const Vec2& v)const override;

	void drawFrame(const Vec2& pos, const Vec2& v)const override;

	void shot(const Vec2& pos, const Vec2& v)override;

	void update() override;

	void beamUpdate();

	void beamCollision();

	void changeState(int nextState)
	{
		m_state = nextState;
		m_stateTimer = 0;
	}

	void texUpdate()override{}
};

class OrangeShot1 : public Shot
{
public:
	Texture m_tex = Texture(L"Resource/Hero//Equip/yellow-1.png");
	Texture m_frameTex = Texture(L"Resource/Hero//Equip/FrameLine/yellowline_1.png");

	OrangeShot1(GameBase* gb);
	void draw(const Vec2& pos, const Vec2& v)const override;

	void  drawFrame(const Vec2& pos, const Vec2& v)const override;

	void shot(const Vec2& pos, const Vec2& v)override;

	void texUpdate()override{}
};

class PurpleShot1 : public Shot
{
public:
	double m_theta = -0.3;

	static int m_life;
	static int m_lifeTimer;

	Texture m_tex = Texture(L"Resource/Hero/Equip/purple-1.png");
	Texture m_frameTex = Texture(L"Resource/Hero//Equip/FrameLine/purpleline_1.png");

	PurpleShot1(GameBase* gb);

	void draw(const Vec2& pos, const Vec2& v)const override;

	void  drawFrame(const Vec2& pos, const Vec2& v)const override;

	void shot(const Vec2& pos, const Vec2& v)override;

	void texUpdate()override;
};

class WhiteShot : public Shot
{
public:

	WhiteShot(GameBase* gb) :Shot(gb, 75, none) 
	{}

	void draw(const Vec2& pos, const Vec2& v)const override
	{
	}


	void drawFrame(const Vec2& pos, const Vec2& v)const override
	{
	}

	void shot(const Vec2& pos, const Vec2& v)override;

	void texUpdate()override{}

};


}