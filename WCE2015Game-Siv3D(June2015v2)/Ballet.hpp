#pragma once
#include<Siv3D.hpp>
#include"Camera.hpp"
#include"ImageAsset.hpp"


namespace shimi
{

class BalletManager;

class Entity
{
public:

	Entity(){}

	Entity(const Vec2& p) :m_pos(p)
	{}

	virtual void draw(const D2Camera& camera)const = 0;

	virtual void move() = 0;

	//オブジェクトを削除してよい状態かどうか
	virtual bool isDead(const D2Camera& camera)
	{
		return !Window::ClientRect().movedBy(-camera.getDrawPos({ 0.0, 0.0 }).asPoint()).intersects(m_pos);//デフォルトは画面から出た時
	}

	Vec2 m_pos;

protected:



};

class Ballet : public Entity
{
protected:
	//TextureとImageを一度に指定するタグ
	String m_balletPictureLabel;

	BalletManager* m_manager;

public:

	Ballet(){}

	Ballet(BalletManager* bm, const String& bpl, const Vec2& p) :Entity(p), m_manager(bm), m_balletPictureLabel(bpl){}

	void draw(const D2Camera& camera) const override
	{
		//Circle(pos, 5).draw(Palette::Green);
		TextureAsset(m_balletPictureLabel).drawAt(camera.getDrawPos(m_pos));
		
	}

	virtual void drop(Image& img)
	{
		ImageAsset::inst()->access(m_balletPictureLabel).write(img, m_pos.asPoint() - TextureAsset(m_balletPictureLabel).size / 2, Alpha(128));
	}

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
};

class BalletAVR : public Ballet
{
protected:

	double velocity;

	double accel;

	double dir;

	double dirv;

public:

	BalletAVR(BalletManager* bm, const String& btl, const Vec2& p, double v = 0.0, double d = 90.0 / 360.0 * Pi, double a = 0.0, double dv = 0.0)
		:
		Ballet(bm, btl, p),
		velocity(v),
		accel(a),
		dir(d),
		dirv(dv)
	{}

	void draw(const D2Camera& camera) const override
	{
		//Circle(pos, 5).draw(Palette::Green);
		TextureAsset(m_balletPictureLabel).rotate(dir + Pi / 2.0).drawAt(camera.getDrawPos(m_pos));
	}

	void move() override
	{
		m_pos += velocity * Vec2(Cos(dir), Sin(dir));

		velocity += accel;

		dir += dirv;
	}
};

/*保留
class BalletXY : public Ballet
{
public:

	BalletXY(const Point& p, const Vec2& v, const Vec2& a = { 0.0, 0.0 })
		:Ballet(p),
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