#pragma once
#include<Siv3D.hpp>
#include"Camera.hpp"


namespace shimi
{

class BalletManager;

class MREntity
{
public:

	MREntity(){}

	MREntity(const Vec2& p) :pos(p)
	{}

	virtual void draw()const = 0;

	virtual void move() = 0;

	//オブジェクトを削除してよい状態かどうか
	virtual bool isDead()
	{
		return !Window::ClientRect().intersects(pos);//デフォルトは画面から出た時
	}


protected:

	Vec2 pos;

};

class MRBallet : public MREntity
{
public:

	MRBallet(){}

	MRBallet(const Vec2& p, const String& btl) :MREntity(p), balletTextureLabel(btl){}

	void draw() const override
	{
		//Circle(pos, 5).draw(Palette::Green);
		TextureAsset(balletTextureLabel).draw();
		
	}

	virtual void move() override
	{
		pos.y -= 5;
	}

	inline Vec2 getPos()const
	{ return pos; }
	
protected:
	String balletTextureLabel;

};

class MRBalletAVR : public MRBallet
{
protected:
	Vec2 posD;

	double velocity;

	double accel;

	double dir;

	double dirv;

	BalletManager* m_manager;


public:

	MRBalletAVR(BalletManager* bm, const Point& p, const String& btl, double v = 0.0, double d = 90.0 / 360.0 * Pi, double a = 0.0, double dv = 0.0)
		:
		m_manager(bm),
		MRBallet(p, btl),
		posD(p),
		velocity(v),
		accel(a),
		dir(d),
		dirv(dv)
	{}

	void draw() const override
	{
		//Circle(pos, 5).draw(Palette::Green);
		TextureAsset(balletTextureLabel).rotate(dir + Pi / 2.0).draw(pos);
	}

	void move() override
	{
		posD += velocity * Vec2(Cos(dir), Sin(dir));

		velocity += accel;

		dir += dirv;

		pos = posD.asPoint();
	}

};

/*保留
class MRBalletXY : public MRBallet
{
public:

	MRBalletXY(const Point& p, const Vec2& v, const Vec2& a = { 0.0, 0.0 })
		:MRBallet(p),
		posD(p),
		velocity(v),
		accel(a)
	{}

	void draw() const override
	{
		//Circle(pos, 5).draw(Palette::Green);
		TextureAsset(L"mame").rotate(Circular(posD).theta).draw(pos);
	}

	void move() override
	{
		posD += velocity;

		velocity += accel;

		pos = posD.asPoint();
	}

protected:
	Vec2 posD;

	Vec2 velocity;

	Vec2 accel;
};
*/
}