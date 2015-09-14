#include "GameBase.hpp"

shimi::GameBase::GameBase() :
	m_tex(L"Resource/Paper2.png")
{
	/*
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(&m_EM, { 720.0, 2250.0 }, Anime(TextureAsset(L"enemy1"), 6, 2), ItemRecord{ShimiColors::Blue, 50} )));
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(&m_EM, { 1000.0, 2000.0 }, Anime(TextureAsset(L"enemy1"), 6, 2), ItemRecord{ ShimiColors::Blue, 50 })));
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(&m_EM, { 1300.0, 2200.0 }, Anime(TextureAsset(L"enemy1"), 6, 2), ItemRecord{ ShimiColors::Blue, 50 })));
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(&m_EM, { 1700.0, 2300.0 }, Anime(TextureAsset(L"enemy1"), 6, 2), ItemRecord{ ShimiColors::Blue, 50 })));
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(&m_EM, { 1650.0, 2450.0 }, Anime(TextureAsset(L"enemy1"), 6, 2), ItemRecord{ ShimiColors::Blue, 50 })));
	*/

	m_EM.registerEnemy(std::shared_ptr<Enemy>(new BasicEnemy(&m_EM, { 720.0, 2250.0 }, AnimeAsset::I()->Asset(L"blueFly"), ShimiColors::Blue, ItemRecord{ ShimiColors::Blue, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new AdvanceEnemy(&m_EM, { 1000.0, 2000.0 }, AnimeAsset::I()->Asset(L"blueFly"), ShimiColors::Blue, ItemRecord{ ShimiColors::Blue, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new BasicEnemy(&m_EM, { 1300.0, 2200.0 }, AnimeAsset::I()->Asset(L"blueFly"), ShimiColors::Blue, ItemRecord{ ShimiColors::Blue, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new AdvanceEnemy(&m_EM, { 1700.0, 2300.0 }, AnimeAsset::I()->Asset(L"blueFly"), ShimiColors::Blue, ItemRecord{ ShimiColors::Blue, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new BasicEnemy(&m_EM, { 1650.0, 2450.0 }, AnimeAsset::I()->Asset(L"blueFly"), ShimiColors::Blue, ItemRecord{ ShimiColors::Blue, 50 })));

	m_EM.registerEnemy(std::shared_ptr<Enemy>(new BasicEnemy(&m_EM, { 850.0, 850.0 }, AnimeAsset::I()->Asset(L"mossEye"), ShimiColors::Green, ItemRecord{ ShimiColors::Green, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new BasicEnemy(&m_EM, { 960.0, 820.0 }, AnimeAsset::I()->Asset(L"mossEye"), ShimiColors::Green, ItemRecord{ ShimiColors::Green, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new BasicEnemy(&m_EM, { 1050.0, 690.0 }, AnimeAsset::I()->Asset(L"mossEye"), ShimiColors::Green, ItemRecord{ ShimiColors::Green, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new AdvanceEnemy(&m_EM, { 1100.0, 1000.0 }, AnimeAsset::I()->Asset(L"blueFly"), ShimiColors::Green, ItemRecord{ ShimiColors::Green, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new AdvanceEnemy(&m_EM, { 1100.0, 1100.0 }, AnimeAsset::I()->Asset(L"blueFly"), ShimiColors::Green, ItemRecord{ ShimiColors::Green, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new AdvanceEnemy(&m_EM, { 650.0, 950.0 }, AnimeAsset::I()->Asset(L"blueFly"), ShimiColors::Green, ItemRecord{ ShimiColors::Green, 50 })));


	m_EM.popForce(m_mv.m_pos, ConfigParam::POP_DISTANCE_IN);

	m_obstacles.push_back(Obstacle({ 0, 0 }, L"Resource/Object/Stage1.png", 3.0));
}

void shimi::GameBase::update()
{
	m_EM.pop();

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
		e.update();
	}

	collisionEnemyWithBallet();

	collisionBalletWithObstacle();

	collisionPlayerWithEnemy();


	Erase_if(m_myBM.m_ballets, [this](const std::shared_ptr<Ballet>& b){return b->isDead(); });

	EffectManager::I()->effect.update();

	m_EM.depop();
}

void shimi::GameBase::draw()const
{
	m_tex.map(6000, 8000).draw(D2Camera::I()->getDrawPos({ 0,0 }), Alpha(70));

	m_mv.draw();

	for (const auto& e : m_EM.m_enemies)
	{
		e.draw();
	}

	for (const auto& b : m_myBM.m_ballets)
	{
		b->draw();
	}	

	m_mv.drawShotEquip();

#ifdef _DEBUG
	m_idb.debug();
	FontAsset(L"Debug").draw(Format(m_EM.m_enemies.size()), {(0,0),(0,0)}, Palette::Black);
#endif 



}

void shimi::GameBase::collisionBalletWithObstacle()
{
	Erase_if(m_myBM.m_ballets, [&](const std::shared_ptr<Ballet>& b)
	{
		bool col = AnyOf(m_obstacles, [&b](const Obstacle& o)
		{
			const bool f = o.m_pols.intersects(Circle(b->m_pos, 5));
			//もしbとeが衝突していたら
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


void shimi::GameBase::collisionEnemyWithBallet()
{
	Erase_if(m_myBM.m_ballets, [&](const std::shared_ptr<Ballet>& b)
	{
		if (AnyOf(m_EM.m_enemies, [&b, this](const CoEnemy& e)
		{
			const bool f = (e.m_enemy->m_pos.distanceFrom(b->m_pos) < 20);
			//もしbとeが衝突していたら, 敵は消滅＆消滅に伴うアイテム処理とエフェクト発生
			if (f)
			{
				e.m_enemy->m_isDead = true;

				EffectManager::I()->effect.add<VanishingEnemy>(e.m_enemy->m_pos.asPoint(), 25.0, 0.5);

				if (e.m_enemy->m_itemID && !m_idb.isgot(e.m_enemy->m_itemID.value()))
				{
					const int index = e.m_enemy->m_itemID.value();

					m_mv.addShotExp(m_idb.m_list[index]);

					m_idb.got(index);
				}


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


void shimi::GameBase::collisionPlayerWithEnemy()const
{
	if (AnyOf(m_EM.m_enemies, [this](const CoEnemy& e){ return e.m_enemy->m_pos.distanceFrom(m_mv.m_pos) < 20; }))
	{
		//Println(L"Attacked!");
	}
}