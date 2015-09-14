#pragma once
#include<Siv3D.hpp>

namespace shimi
{

class GameBase;

class ShotGenerator
{
protected:
	GameBase* m_gb;

	TimerMillisec timer;//処理の時間の終わり管理用

	unsigned int deadLine;//終わりの時間

public:
	bool isDead;//削除して良い状態かどうか

	ShotGenerator();

	ShotGenerator(GameBase* gb, unsigned int dl) :isDead(false), deadLine(dl), m_gb(gb)
	{}

	void start(){ timer.restart(); }

	virtual void generate(const Vec2& vehiclePos, const Vec2& vehicleV) = 0;

	void update(const Vec2& vehiclePos, const Vec2& vehicleV)
	{
		if (isDead) return;

		if (timer.elapsed() > deadLine)
		{
			isDead = true;
			return;
		}

		generate(vehiclePos, vehicleV);
	}
};

class ShotRound : public ShotGenerator
{
public:

	ShotRound(){}

	ShotRound(GameBase* gb, unsigned int dl, const Vec2& p) :ShotGenerator(gb, dl), pos(p)
	{
		wait.start();
	}

	void generate(const Vec2& vehiclePos, const Vec2& vehicleV)override;
private:
	TimerMillisec wait;

	Vec2 pos;//発射基準点
};

class ShotSakura : public ShotGenerator
{
public:

	ShotSakura(){}

	ShotSakura(GameBase* gb, unsigned int dl) :ShotGenerator(gb, dl)
	{
		wait.start();
	}

	void generate(const Vec2& vehiclePos, const Vec2& vehicleV)override;
private:
	TimerMillisec wait;
};

class ShotChase : public ShotGenerator
{
public:

	ShotChase(){}

	ShotChase(GameBase* gb, unsigned int dl) :ShotGenerator(gb, dl)
	{
		wait.start();
	}

	void generate(const Vec2& vehiclePos, const Vec2& vehicleV)override;

private:
	TimerMillisec wait;
};

class ShotOugi : public ShotGenerator
{
public:
	ShotOugi(){}
	ShotOugi(GameBase* gb, unsigned int dl) :ShotGenerator(gb, dl)
	{
		wait.start();
	}

	void generate(const Vec2& vehiclePos, const Vec2& vehicleV)override;

private:
	TimerMillisec wait;
};

}