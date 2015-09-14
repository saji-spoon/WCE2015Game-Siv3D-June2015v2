#pragma once
#include<Siv3D.hpp>

namespace shimi
{

class GameBase;

class ShotGenerator
{
protected:
	GameBase* m_gb;

	TimerMillisec timer;//�����̎��Ԃ̏I���Ǘ��p

	unsigned int deadLine;//�I���̎���

public:
	bool isDead;//�폜���ėǂ���Ԃ��ǂ���

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

	Vec2 pos;//���ˊ�_
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