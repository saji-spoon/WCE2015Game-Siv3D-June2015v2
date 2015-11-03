#pragma once
#include<Siv3D.hpp>

namespace shimi
{

class GameBase;

class ShotGenerator
{
protected:
	GameBase* m_gb;

	int m_timer;//ˆ—‚ÌŠÔ‚ÌI‚í‚èŠÇ——p

public:

	ShotGenerator();

	ShotGenerator(GameBase* gb, int deadLine) :m_gb(gb), m_timer(deadLine)
	{}

	virtual void generate(const Vec2& vehiclePos, const Vec2& vehicleV) = 0;

	virtual void update(const Vec2& vehiclePos, const Vec2& vehicleV)
	{
		generate(vehiclePos, vehicleV);
		--m_timer;
	}

	virtual void draw(const Vec2& vehiclePos, const Vec2& vehicleV) = 0;

	virtual bool isDead()
	{ 
		return m_timer <= 0;
	}
};

class BlueShot1Generator : public ShotGenerator
{
public:

	Vec2 m_pos;

	int m_waitTimer;

	int m_count = 0;

	BlueShot1Generator(){}

	BlueShot1Generator(GameBase* gb, int dl, const Vec2& p) :ShotGenerator(gb, dl), m_pos(p)
	{
	}

	void draw(const Vec2& vehiclePos, const Vec2& vehicleV);

	void generate(const Vec2& vehiclePos, const Vec2& vehicleV)override;
};

}