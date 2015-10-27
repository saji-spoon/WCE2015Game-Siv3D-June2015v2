#include "GameBase.hpp"
#include"Effect.hpp"
#include"State.hpp"
#include"AwakePlayerAttack.hpp"
#include"EnemyShot.hpp"
#include"BGMManager.hpp"

shimi::GameBase::GameBase() :
m_tex(L"Resource/Paper2.png"), m_state(new state::MainGame()), m_menu(this, m_mv)
{
	/*
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(&m_EM, { 720.0, 2250.0 }, Anime(TextureAsset(L"enemy1"), 6, 2), ItemRecord{ShimiColors::Blue, 50} )));
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(&m_EM, { 1000.0, 2000.0 }, Anime(TextureAsset(L"enemy1"), 6, 2), ItemRecord{ ShimiColors::Blue, 50 })));
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(&m_EM, { 1300.0, 2200.0 }, Anime(TextureAsset(L"enemy1"), 6, 2), ItemRecord{ ShimiColors::Blue, 50 })));
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(&m_EM, { 1700.0, 2300.0 }, Anime(TextureAsset(L"enemy1"), 6, 2), ItemRecord{ ShimiColors::Blue, 50 })));
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(&m_EM, { 1650.0, 2450.0 }, Anime(TextureAsset(L"enemy1"), 6, 2), ItemRecord{ ShimiColors::Blue, 50 })));
	*/

	StraightShot case1(this, { { Vec2{ 0, 2.0 }, 180 } }, BalletAVR(&m_enemyBM, L"enemyBallet1", ShimiColors::Red, Vec2(0, 0), 0.0, 0.0), true);

	
	const std::shared_ptr<EnemyShot> push1(new StraightShot(this, { { Vec2{ 0, 1 }, 180 } }, BalletAVR(&m_enemyBM, L"enemyBallet1", ShimiColors::Red, Vec2(0, 0), 0.0, 0.0), true));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new StopEnemy(&m_EM, { 600, 4900.0 }, AnimeAsset::I()->Asset(L"redDia"), std::shared_ptr<EnemyShot>(new StraightShot(case1)), ShimiColors::Red, ItemRecord{ ShimiColors::Red, 1 })));
	case1.m_schedule = { { Vec2{ -2.0, 0 }, 180 } };
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new StopEnemy(&m_EM, { 898, 5140.0 }, AnimeAsset::I()->Asset(L"redDia"), std::shared_ptr<EnemyShot>(new StraightShot(case1)), ShimiColors::Red, ItemRecord{ ShimiColors::Red, 1 })));

	case1.m_schedule = { { Vec2{ -2.0, 0 }, 180 } };
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new StopEnemy(&m_EM, { 1400, 5256.0 }, AnimeAsset::I()->Asset(L"redDia"), std::shared_ptr<EnemyShot>(new StraightShot(case1)), ShimiColors::Red, ItemRecord{ ShimiColors::Red, 1 })));
	
	case1.m_schedule = { { Vec2{ 0.0, 2.0 }, 180 } };
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new StopEnemy(&m_EM, { 1062, 4982.0 }, AnimeAsset::I()->Asset(L"redDia"), std::shared_ptr<EnemyShot>(new StraightShot(case1)), ShimiColors::Red, ItemRecord{ ShimiColors::Red, 1 })));
	case1.m_schedule = { { Vec2{ 0.0, -2.0 }, 180 } }; 
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new StopEnemy(&m_EM, { 1272, 5423.0 }, AnimeAsset::I()->Asset(L"redDia"), std::shared_ptr<EnemyShot>(new StraightShot(case1)), ShimiColors::Red, ItemRecord{ ShimiColors::Red, 1 })));
	
	case1.m_schedule = { { Vec2{ -2.0, 0.0 }, 180 } };
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new StopEnemy(&m_EM, { 1853, 5650.0 }, AnimeAsset::I()->Asset(L"redDia"), std::shared_ptr<EnemyShot>(new StraightShot(case1)), ShimiColors::Red, ItemRecord{ ShimiColors::Red, 1 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new StopEnemy(&m_EM, { 1853, 5750.0 }, AnimeAsset::I()->Asset(L"redDia"), std::shared_ptr<EnemyShot>(new StraightShot(case1)), ShimiColors::Red, ItemRecord{ ShimiColors::Red, 1 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new StopEnemy(&m_EM, { 1853, 5850.0 }, AnimeAsset::I()->Asset(L"redDia"), std::shared_ptr<EnemyShot>(new StraightShot(case1)), ShimiColors::Red, ItemRecord{ ShimiColors::Red, 1 })));

	m_EM.registerEnemy(std::shared_ptr<Enemy>(new StopEnemy(&m_EM, { 1362, 5900.0 }, AnimeAsset::I()->Asset(L"redDia"), std::shared_ptr<EnemyShot>(new StraightShot(case1)), ShimiColors::Red, ItemRecord{ ShimiColors::Red, 1 })));
	case1.m_schedule = { { Vec2{ 0.0, -2.0 }, 180 } };
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new StopEnemy(&m_EM, { 1062, 5900.0 }, AnimeAsset::I()->Asset(L"redDia"), std::shared_ptr<EnemyShot>(new StraightShot(case1)), ShimiColors::Red, ItemRecord{ ShimiColors::Red, 1 })));
	case1.m_schedule = { { Vec2{ 2.0, 0.0 }, 180 } };
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new StopEnemy(&m_EM, { 1062, 5700.0 }, AnimeAsset::I()->Asset(L"redDia"), std::shared_ptr<EnemyShot>(new StraightShot(case1)), ShimiColors::Red, ItemRecord{ ShimiColors::Red, 1 })));
	case1.m_schedule = { { Vec2{ 0.0, 2.0 }, 180 } };
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new StopEnemy(&m_EM, { 1362, 5700.0 }, AnimeAsset::I()->Asset(L"redDia"), std::shared_ptr<EnemyShot>(new StraightShot(case1)), ShimiColors::Red, ItemRecord{ ShimiColors::Red, 1 })));

	/*
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new AdvanceEnemy(&m_EM, { 1000.0, 2000.0 }, AnimeAsset::I()->Asset(L"blueFly"), ShimiColors::Blue, ItemRecord{ ShimiColors::Blue, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new BasicEnemy(&m_EM, { 1300.0, 2200.0 }, AnimeAsset::I()->Asset(L"blueFly"), ShimiColors::Blue, ItemRecord{ ShimiColors::Blue, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new AdvanceEnemy(&m_EM, { 1700.0, 2300.0 }, AnimeAsset::I()->Asset(L"blueFly"), ShimiColors::Blue, ItemRecord{ ShimiColors::Blue, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new BasicEnemy(&m_EM, { 1650.0, 2450.0 }, AnimeAsset::I()->Asset(L"blueFly"), ShimiColors::Blue, ItemRecord{ ShimiColors::Blue, 50 })));

	m_EM.registerEnemy(std::shared_ptr<Enemy>(new BasicEnemy(&m_EM, { 850.0, 850.0 }, AnimeAsset::I()->Asset(L"mossEye"), ShimiColors::Green, ItemRecord{ ShimiColors::Red, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new BasicEnemy(&m_EM, { 960.0, 820.0 }, AnimeAsset::I()->Asset(L"mossEye"), ShimiColors::Green, ItemRecord{ ShimiColors::Red, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new BasicEnemy(&m_EM, { 1050.0, 690.0 }, AnimeAsset::I()->Asset(L"mossEye"), ShimiColors::Green, ItemRecord{ ShimiColors::Red, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new AdvanceEnemy(&m_EM, { 1100.0, 1000.0 }, AnimeAsset::I()->Asset(L"blueFly"), ShimiColors::Green, ItemRecord{ ShimiColors::Red, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new AdvanceEnemy(&m_EM, { 1100.0, 1100.0 }, AnimeAsset::I()->Asset(L"blueFly"), ShimiColors::Green, ItemRecord{ ShimiColors::Red, 50 })));
	m_EM.registerEnemy(std::shared_ptr<Enemy>(new AdvanceEnemy(&m_EM, { 650.0, 950.0 }, AnimeAsset::I()->Asset(L"blueFly"), ShimiColors::Green, ItemRecord{ ShimiColors::Red, 50 })));
	*/

	m_EM.popForce(m_mv.m_pos, ConfigParam::POP_DISTANCE_IN);

	m_obstacles.push_back(Obstacle({ 62, 3176 }, L"Resource/Stage_temp/stage_start.png", 12.0));
	/*
	m_obstacles.push_back(Obstacle({ 0, 0 }, L"Resource/Stage_temp/stage_beehive.png", 12.0));
	m_obstacles.push_back(Obstacle(Point{ 1757, 0 }*2, L"Resource/Stage_temp/stage_planet.png", 12.0));
	m_obstacles.push_back(Obstacle(Point{ 1311, 1454 }*2, L"Resource/Stage_temp/stage_crystal.png", 12.0));
	m_obstacles.push_back(Obstacle(Point{ 1002, 1551 }*2, L"Resource/Stage_temp/stage_fish_and_vine.png", 12.0));
	*/

	m_bosses.push_back(std::shared_ptr<Boss>(new Boss1(this, Vec2(1565, 3698))));

	BGMManager::I()->changeBGM(L"NormalStage");
	
}

void shimi::GameBase::mainGameUpdate()
{
	m_EM.pop();

	updateCamera(m_mv.m_pos);

	m_mv.update();

	for (auto& boss : m_bosses)
	{
		boss->update();
	}

	for (auto& b : m_myBM.m_ballets)
	{
		b->update();
	}

	for (auto& b : m_enemyBM.m_ballets)
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

	collisionPlayerWithBallet();


	Erase_if(m_myBM.m_ballets, [this](const std::shared_ptr<Ballet>& b){return b->isDead(); });

	EffectManager::I()->effect.update();

	m_EM.depop();

	if (Input::KeyS.clicked)
	{
		changeState(std::shared_ptr<state::GBState>(new state::Menu()));
	}

#ifdef _DEBUG
	m_debugP.update();
#endif
}

void shimi::GameBase::draw()const
{
	m_tex.map(12000, 8000).draw(D2Camera::I()->getDrawPos({ 0,0 }), Alpha(70));

	m_mv.draw();

	for (auto& boss : m_bosses)
	{
		boss->draw();
	}

	for (const auto& o : m_obstacles)
	{
		o.draw();
	}

	for (const auto& e : m_EM.m_enemies)
	{
		e.draw();
	}

	for (const auto& b : m_myBM.m_ballets)
	{
		b->draw();
	}	

	for (const auto& b : m_enemyBM.m_ballets)
	{
		b->draw();
	}

	m_mv.drawShotEquip();

#ifdef _DEBUG
	m_idb.debug();
	FontAsset(L"Debug").draw(Format(m_EM.m_enemies.size()), {(0,0),(0,0)}, Palette::Black);

	FontAsset(L"Debug").draw(Format(m_mv.m_pos.asPoint()), D2Camera::I()->getGlobalPos(m_mv.m_pos), Palette::Black);

	m_debugP.draw();


#endif 



}

void shimi::GameBase::collisionBalletWithObstacle()
{
	Erase_if(m_myBM.m_ballets, [&](const std::shared_ptr<Ballet>& b)
	{
		bool col = AnyOf(m_obstacles, [&b](const Obstacle& o)
		{
			if (b->m_shimiColor == ShimiColors::Purple) return false;

			const bool f = o.m_pols.intersects(Circle(b->m_pos, 5));
			//Ç‡ÇµbÇ∆eÇ™è’ìÀÇµÇƒÇ¢ÇΩÇÁ
			if (f)
			{
				b->m_isDead = true;

				EffectManager::I()->effect.add<VanishingBallet>(b->m_pos.asPoint(), 13, 0.5);

			}
			return f;
		});

		return col;
	});

	//ìGÇÃíeÇÃè’ìÀ
	Erase_if(m_enemyBM.m_ballets, [&](const std::shared_ptr<Ballet>& b)
	{
		bool col = AnyOf(m_obstacles, [&b](const Obstacle& o)
		{
			if (b->m_shimiColor == ShimiColors::Purple) return false;

			const bool f = o.m_pols.intersects(Circle(b->m_pos, 5));
			//Ç‡ÇµbÇ∆eÇ™è’ìÀÇµÇƒÇ¢ÇΩÇÁ
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
		const bool isHit = AwakePlayerAttack(this, b->m_pos, b->m_shimiColor, 20);

		if (isHit) EffectManager::I()->effect.add<VanishingBallet>(b->m_pos.asPoint(), 13, 0.5);

		return isHit;
	});
}

void shimi::GameBase::collisionPlayerWithBallet()
{
	Erase_if(m_enemyBM.m_ballets, [&](const std::shared_ptr<Ballet>& b)
	{
		const bool isHit = AwakeEnemyAttack(this, b->m_pos, b->m_shimiColor, 20);

		return isHit;
	});
}

void shimi::GameBase::collisionPlayerWithEnemy()
{
	for (const auto& e : m_EM.m_enemies)
	{
		AwakeEnemyAttack(this, Circle(e.m_enemy->m_pos, 20), e.m_enemy->m_shimiColor, 1);
	}

	/*
	if (AnyOf(m_EM.m_enemies, [this](const CoEnemy& e){ return e.m_enemy->m_pos.distanceFrom(m_mv.m_pos) < 20; }))
	{
		//Println(L"Attacked!");
	}*/
}

void shimi::GameBase::changeState(const std::shared_ptr<state::GBState>& state)
{
	m_state->exit(this);
	m_state = state;
	m_state->enter(this);
}