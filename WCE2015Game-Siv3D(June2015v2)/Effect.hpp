#pragma once
#include<Siv3D.hpp>
#include"Camera.hpp"
#include"ShimiColors.hpp"
#include"SimpleState.hpp"
#define TOUINT(a) static_cast<uint32>(a)

namespace shimi
{

class GameBase;

class VanishingBallet : public IEffect
{
public:

	Point m_pos;

	double m_r;

	double m_limitTime;

	VanishingBallet(const Point& pos, double size, double limit) :m_pos(pos), m_r(size), m_limitTime(limit)
	{
		
	}

	bool update(double t) override;
};

class VanishingEnemy : public IEffect
{
public:

	Point m_pos;

	double m_r;

	double m_limitTime;

	ShimiColors m_col;

	VanishingEnemy(const Point& pos, double size, double limit, const ShimiColors& col) :m_pos(pos), m_r(size), m_limitTime(limit), m_col(col)
	{

	}

	bool update(double t) override;
};

struct Particle
{
	Particle(){}

	Particle(const Vec2& pos, bool isDead = false)
		:m_pos(pos),
		m_isDead(isDead)
	{}

	Vec2 m_pos;
	bool m_isDead;
};

struct NotifyStr
{
	String m_str;

	Vec2 m_flow = Vec2(0,0);

	Color m_col;

	int m_stopTime;

	int m_timer = 0;

	NotifyStr(const String& str, const Color& col, int stopTime);

	void draw(const Vec2& pos)const;

	void update();

};

struct NotifyStr2
{
	String m_str1;
	String m_str2;

	Vec2 m_flow = Vec2(0, 0);

	Color m_col1;
	Color m_col2;

	Font m_font;

	int m_stopTime;

	int m_timer = 0;

	NotifyStr2(const String& str1, const String& str2,  const Color& col1, int stopTime, const Color& col2);

	void draw(const Vec2& pos)const;

	void update();

};

class ItemGet :public IEffect
{
public:
	GameBase* m_gb;

	double m_speed = 8.0;

	ShimiColors m_col;

	NotifyStr m_str;

	int m_val;

	std::vector<Particle> m_particles;

	ItemGet(GameBase* gb, const Vec2& pos, const ShimiColors& col, int val);

	bool update(double t) override;

};

class Notify : public IEffect
{
public:

	GameBase* m_gb;

	NotifyStr2 m_str;

	Notify(GameBase* gb, const NotifyStr2& notify);

	bool update(double t) override;
};

struct TimedParticle
{
	TimedParticle(const Vec2& pos, int limit, const Vec2& v = Vec2(0.0, 0.0), const Vec2& a = Vec2(0.0, 0.0))
		:m_pos(pos), m_v(v), m_a(a), m_limit(limit)
	{}

	void update()
	{
		++m_timer;

		m_pos += m_v;
		m_v += m_a;

		if (m_timer >= m_limit) kill();
	}

	inline bool isDead()const
	{
		return m_isDead;
	}

	inline void kill()
	{
		m_isDead = true;
	}
	Vec2 m_pos;
	Vec2 m_v;
	Vec2 m_a;

	int m_timer = 0;

	int m_limit;

private:
	bool m_isDead = false;


};


class BossWarp :public IEffect
{
public:

	SimpleState m_s;

	Vec2 m_pos;

	double m_size;

	std::vector<TimedParticle> m_particles;

	BossWarp(const Vec2& pos, const double size) :m_pos(pos), m_size(size), m_s(20)
	{
	}

	bool update(double t) override;

};

class BossVanish : public IEffect
{
public:

	EasingController<double> m_easing;

	SimpleState m_s;

	Vec2 m_pos;

	double m_size;

	std::vector<TimedParticle> m_particles;

	BossVanish(const Vec2& pos, const double size) :
		m_pos(pos),
		m_size(size),
		m_s(20),
		m_easing(0.0, size, Easing::Quint, 200)
	{
		for (int i = 0; i < 10; ++i)
		{
			m_particles.push_back(TimedParticle(pos, 60, RandomVec2(3.0), Vec2(0, -0.3)));
		}

		m_easing.start();
	}


	bool update(double t) override;


};

class Vanishing :public IEffect
{
public:
	Color m_col;
	int m_size;

	double speed;

	double progress = 0.0;

	Vec2 m_pos;

	Vanishing(const Vec2& pos, int size, const Color& col)
		:m_pos(pos),
		m_size(size),
		m_col(col),
		speed(1.0*size / 12.0)
	{
	}

	bool update(double t)override;

};

class VanishingMV : public Vanishing
{
public:

	VanishingMV(const Vec2& pos, int size, const Color& col)
		:Vanishing(pos, size, col)

	{
	}

	bool update(double t)override;

};


class Charging : public IEffect
{
public:

	int m_timer = 0;

	Vec2 m_pos;

	Charging(){}

	Charging(const Vec2& pos)
		:m_pos(pos)
	{
	}

	bool update(double t)override;
};

}
