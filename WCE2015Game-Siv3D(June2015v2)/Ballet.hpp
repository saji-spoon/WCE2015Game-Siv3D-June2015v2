#pragma once
#pragma warning( disable : 4100 )
#include<Siv3D.hpp>
#include"Camera.hpp"
#include"ShimiColors.hpp"
#include"DropManager.hpp"

namespace shimi
{

class BalletManager;

class Entity
{
public:

	Entity(){}

	Entity(const Vec2& p) :m_pos(p)
	{}

	virtual ~Entity(){}

	virtual void draw()const = 0;

	virtual void move() = 0;

	//オブジェクトを削除してよい状態かどうか
	virtual bool isDead()
	{
		return !Window::ClientRect().movedBy(-D2Camera::I()->getDrawPos({ 0.0, 0.0 }).asPoint()).intersects(m_pos);//デフォルトは画面から出た時
	}

	Vec2 m_pos;

protected:



};

class Ballet : public Entity
{
public:
	bool m_isDead = false;

	Optional<ShimiColors> m_shimiColor;

	//TextureとImageを一度に指定するタグ
	String m_balletPictureLabel;

	BalletManager* m_manager;

public:

	Ballet(){}

	Ballet(BalletManager* bm, const String& bpl, const Vec2& p, const Optional<ShimiColors>& col) :Entity(p), m_manager(bm), m_balletPictureLabel(bpl), m_shimiColor(col)
	{}

	virtual ~Ballet(){}

	void draw() const override
	{
		//Circle(pos, 5).draw(Palette::Green);
		TextureAsset(m_balletPictureLabel).drawAt(D2Camera::I()->getDrawPos(m_pos));
		
	}

	virtual void drop() = 0;

	virtual void update()
	{
		move();
	}

	virtual void move() override
	{
		m_pos.y -= 5;
	}

	inline Vec2 getPos()const
	{ return m_pos; }

	virtual bool isDead()
	{
		return !Window::ClientRect().movedBy(-D2Camera::I()->getDrawPos({ 0.0, 0.0 }).asPoint()).intersects(m_pos) || m_isDead;//デフォルトは画面から出た時
	}
};

class BalletAVR : public Ballet
{
protected:

	double velocity;

	double accel;

	double dir;

	double dirv;

	Optional<ScheduleTimer> m_dropSchedule;

public:

	BalletAVR(BalletManager* bm, const String& btl, const Optional<ShimiColors>& col, const Vec2& p, double v = 0.0, double d = 90.0 / 360.0 * Pi, double a = 0.0, double dv = 0.0, const Optional<ScheduleTimer>& dropSchdl = none)
		:
		Ballet(bm, btl, p, col),
		velocity(v),
		accel(a),
		dir(d),
		dirv(dv),
		m_dropSchedule(dropSchdl)
	{}

	virtual ~BalletAVR(){}

	void draw() const override
	{
		//Circle(pos, 5).draw(Palette::Green);
		TextureAsset(m_balletPictureLabel).rotate(dir + Pi / 2.0).drawAt(D2Camera::I()->getDrawPos(m_pos));
	}

	virtual void update()override
	{
		move();

		if (m_dropSchedule)
		{
			m_dropSchedule.value().update();

			if (m_dropSchedule.value().isDropTime()) drop();
		}

	}

	void move() override
	{
		m_pos += velocity * Vec2(Cos(dir), Sin(dir));

		velocity += accel;

		dir += dirv;
	}

	void drop()override;


	bool isDead()override
	{

		return !Rect(0, 0, 8000, 6500).intersects(m_pos) || m_isDead;
		//return !Window::ClientRect().movedBy(-D2Camera::I()->getDrawPos({ 0.0, 0.0 }).asPoint()).intersects(m_pos) || m_isDead;//デフォルトは画面から出た時
	}
};

class BalletLimit : public BalletAVR
{
public:
	int m_timer;

	BalletLimit(BalletManager* bm, const String& btl, const Optional<ShimiColors>& col, const Vec2& p, int deadLine, double v = 0.0, double d = 90.0 / 360.0 * Pi, double a = 0.0, double dv = 0.0, const Optional<ScheduleTimer>& dropSchdl = none)
		:
		BalletAVR(bm, btl, col, p, v, d, a, dv, dropSchdl),
		m_timer(deadLine)
	{}

	virtual ~BalletLimit(){}

	void update()override
	{
		if (m_timer <= 0)
		{
			return;
		}

		move();

		if (m_dropSchedule)
		{
			m_dropSchedule.value().update();

			if (m_dropSchedule.value().isDropTime()) drop();
		}

		--m_timer;
	
	}

	bool isDead()override
	{
		return (m_timer <= 0) || m_isDead;
	}

};

}