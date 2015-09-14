#pragma once
#include<Siv3D.hpp>
#include"Ballet.hpp"
#include"AscAnime.hpp"
#include"ItemDatabase.hpp"

namespace shimi
{
class EnemyManager;

using namespace asc;

class Enemy : public Entity 
{
public:
	EnemyManager* m_manager;

	Anime m_anime;

	Optional<int> m_itemID = none;

	int count = 0;

	bool m_isDead = false;

	Enemy(EnemyManager* em, const Vec2 pos, const Anime& anime = Anime(TextureAsset(L"enemy1"), 4, 1), const Optional<ItemRecord> ir = none);

	virtual void draw() const override
	{
		//Circle(camera.getDrawPos(m_pos), 20).draw(Palette::Red);
		m_anime.drawAt(D2Camera::I()->getDrawPos(m_pos));
	}

	virtual void update()
	{
		m_anime.update();
	}

	virtual void move() override
	{
	}

	virtual bool isDead()override
	{
		return m_isDead;
	}
};

}