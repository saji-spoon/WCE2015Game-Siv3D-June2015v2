#pragma once
#include<Siv3D.hpp>
#include"Ballet.hpp"
#include"AscAnime.hpp"

namespace shimi
{
class EnemyManager;

using namespace asc;

class Enemy : public Entity 
{
public:
	EnemyManager* m_manager;

	int count = 0;

	bool m_isDead = false;

	Anime m_anime;

	Enemy(EnemyManager* em, const Vec2 pos, const Anime& anime = Anime(TextureAsset(L"enemy1"), 4, 1)) :m_manager(em), Entity(pos), m_anime(anime)
	{}

	void draw(const D2Camera& camera) const override
	{
		//Circle(camera.getDrawPos(m_pos), 20).draw(Palette::Red);
		m_anime.drawAt(camera.getDrawPos(m_pos));
	}

	virtual void update()
	{
		m_anime.update();
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