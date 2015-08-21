#pragma once
#include<Siv3D.hpp>
#include"Camera.hpp"

namespace shimi
{

class VanishingBallet : public IEffect
{
public:

	Point m_pos;

	double m_r;

	double m_limitTime;

	VanishingBallet(const Point& pos, double size, double limit) :m_pos(pos), m_r(size), m_limitTime(limit)
	{
		
	}

	bool update(double t) override
	{
		const double rate = t / m_limitTime;

		const Vec2 drawPos = D2Camera::I()->getDrawPos(m_pos);
		
		const double diffuse = 255.0 * Saturate((1.0 - rate));

		Circle(drawPos, m_r*(1.0-rate)).draw(Color(55, 122, 238, static_cast<s3d::uint32>(diffuse)));

		return t < m_limitTime;
	}
};


class VanishingEnemy : public IEffect
{
public:

	Point m_pos;

	double m_r;

	double m_limitTime;

	VanishingEnemy(const Point& pos, double size, double limit) :m_pos(pos), m_r(size), m_limitTime(limit)
	{

	}

	bool update(double t) override
	{
		const double rate = t / m_limitTime;

		const Vec2 drawPos = D2Camera::I()->getDrawPos(m_pos);

		const double diffuse = 255.0 * Saturate((1.0 - rate));

		Circle(drawPos, m_r*rate).drawFrame(7.0, 0.0, Color(55, 122, 238, static_cast<s3d::uint32>(diffuse)));
		Circle(drawPos, m_r*rate).drawFrame(0.0, 7.0, Color(104, 160, 255, static_cast<s3d::uint32>(diffuse)));

		return t < m_limitTime;
	}
};

}
