#include "GameBase.hpp"

using namespace shimi;

GameBase::GameBase() :
	m_tex(L"Resource/Paper2.png")
{
	/*for prototype*/

	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(&m_EM, { 720.0, 2250.0 }, Anime(TextureAsset(L"enemy1"), 6, 2), ItemRecord{ShimiColors::Blue, 50} )));
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(&m_EM, { 1000.0, 2000.0 }, Anime(TextureAsset(L"enemy1"), 6, 2), ItemRecord{ ShimiColors::Blue, 50 })));
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(&m_EM, { 1300.0, 2200.0 }, Anime(TextureAsset(L"enemy1"), 6, 2), ItemRecord{ ShimiColors::Blue, 50 })));
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(&m_EM, { 1700.0, 2300.0 }, Anime(TextureAsset(L"enemy1"), 6, 2), ItemRecord{ ShimiColors::Blue, 50 })));
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(&m_EM, { 1650.0, 2450.0 }, Anime(TextureAsset(L"enemy1"), 6, 2), ItemRecord{ ShimiColors::Blue, 50 })));

	m_obstacles.push_back(Obstacle({ 0, 0 }, L"Resource/Object/Stage1.png", 3.0));
}

void GameBase::update()
{
	updateCamera(m_mv.m_pos);

	m_mv.update();

	if (Mouse::RightClicked())
	{
		for (auto& b : m_myBM.m_ballets)
		{
			const Image img(0, 0);
			b->drop(Image(img));
		}
	}

	//std::for_each(m_myBM.m_ballets.begin(), m_myBM.m_ballets.end(), [](const std::shared_ptr<Ballet>& b){ b->update(); });
	for (auto& b : m_myBM.m_ballets)
	{
		b->update();
	}

	for (auto& e : m_EM.m_enemies)
	{
		e->update();
	}

	collisionEnemyWithBallet();

	collisionBalletWithObstacle();

	collisionPlayerWithEnemy();


	Erase_if(m_myBM.m_ballets, [this](const std::shared_ptr<Ballet>& b){return b->isDead(); });


	Erase_if(m_EM.m_enemies, [&](const std::shared_ptr<Enemy>& e){return e->isDead(); });

	EffectManager::I()->effect.update();
}

void GameBase::draw()const
{
	m_tex.map(6000, 8000).draw(D2Camera::I()->getDrawPos({ 0,0 }), Alpha(70));

	m_mv.draw();

	for (const auto& e : m_EM.m_enemies)
	{
		e->draw();
	}

	for (const auto& b : m_myBM.m_ballets)
	{
		b->draw();
	}	

#ifdef _DEBUG
	m_idb.debug();
#endif 



}

void GameBase::collisionBalletWithObstacle()
{
	Erase_if(m_myBM.m_ballets, [&](const std::shared_ptr<Ballet>& b)
	{
		bool col = AnyOf(m_obstacles, [&b](const Obstacle& o)
		{
			const bool f = o.m_pols.intersects(Circle(b->m_pos, 5));
			//‚à‚µb‚Æe‚ªÕ“Ë‚µ‚Ä‚¢‚½‚ç
			if (f)
			{
				b->m_isDead = true;

				EffectManager::I()->effect.add<VanishingBallet>(b->m_pos.asPoint(), 13, 0.5);

			}
			return f;
		});

		return col;
	});
}


void GameBase::collisionEnemyWithBallet()
{
	Erase_if(m_myBM.m_ballets, [&](const std::shared_ptr<Ballet>& b)
	{
		if (AnyOf(m_EM.m_enemies, [&b, this](const std::shared_ptr<Enemy>& e)
		{
			const bool f = (e->m_pos.distanceFrom(b->m_pos) < 20);
			//‚à‚µb‚Æe‚ªÕ“Ë‚µ‚Ä‚¢‚½‚ç
			if (f)
			{
				e->m_isDead = true;

				EffectManager::I()->effect.add<VanishingEnemy>(e->m_pos.asPoint(), 25.0, 0.5);

				if (e->m_itemID) m_idb.got(e->m_itemID.value());

				b->m_isDead = true;

				EffectManager::I()->effect.add<VanishingBallet>(b->m_pos.asPoint(), 13, 0.5);

			}
			return f;
		}))
		{
			return true;
		}
		else
		{
			return false;
		}
	});
}


void GameBase::collisionPlayerWithEnemy()const
{
	if (AnyOf(m_EM.m_enemies, [this](const std::shared_ptr<Enemy>& e){ return e->m_pos.distanceFrom(m_mv.m_pos) < 20; }))
	{
		Println(L"Attacked!");
	}
}