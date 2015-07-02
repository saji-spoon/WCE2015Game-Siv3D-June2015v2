#pragma once
#include<Siv3D.hpp>
#include"Ballet.hpp"

namespace shimi
{
class EnemyManager;

class Enemy : public Entity 
{
public:
	EnemyManager* m_manager;

	int count = 0;

	bool m_isDead = false;

	Enemy(EnemyManager* em, const Vec2 pos) :m_manager(em), Entity(pos)
	{}

	void draw(const D2Camera& camera) const override
	{
		Circle(camera.getDrawPos(m_pos), 20).draw(Palette::Red);
	}

	virtual void update()
	{
	}

	virtual void move() override
	{
	}

	virtual bool isDead(const D2Camera& camera)override
	{
		return m_isDead;
	}
};


}