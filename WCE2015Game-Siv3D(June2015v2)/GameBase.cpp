#include "GameBase.hpp"

using namespace shimi;

GameBase::GameBase() :
	m_camera(m_mv.m_pos),
	m_tex(L"Resource/Paper2.png")
{
	/*for prototype*/

	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy( &m_EM, { 720.0, 2150.0 }, Anime( TextureAsset(L"enemy1"), 4, 5 ) )));
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy( &m_EM, { 1000.0, 1900.0 }, Anime(TextureAsset(L"enemy1"), 4, 5))));
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy( &m_EM, { 1300.0, 2200.0 }, Anime(TextureAsset(L"enemy1"), 4, 5))));

	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(
		&m_EM, { 1700.0, 2300.0 }, Anime(TextureAsset(L"enemy2"), 13, 3
		))));

	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(
		&m_EM, { 1650.0, 2450.0 }, Anime(TextureAsset(L"enemy2"), 13, 3
		))));

	m_obstacles.push_back(Obstacle({ 0, 0 }, L"Resource/Object/Stage1.png", 3.0));
}

void GameBase::update()
{
	updateCamera(m_mv.m_pos);

	m_mv.update();

	collisionPlayerWithEnemy();

	/*ショット機能はMyVechicleへ
	if (Mouse::LeftClicked())
	{
		
		m_myBM.m_ballets.push_back(Ballet(&m_myBM, L"ballet.png", getMyVehiclePos()));

		Println(Profiler::FPS());
	}
	*/

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

	Erase_if(m_myBM.m_ballets, [this](const std::shared_ptr<Ballet> b){return b->isDead(m_camera); });

	Erase_if(m_myBM.m_ballets, [&](const std::shared_ptr<Ballet>& b)
	{
		if (AnyOf(m_EM.m_enemies, [b](const std::shared_ptr<Enemy>& e)
			{ 
				const bool f = (e->m_pos.distanceFrom(b->m_pos) < 20);
				if (f) { e->m_isDead = true; }
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

	Erase_if(m_EM.m_enemies, [&](const std::shared_ptr<Enemy>& e){return e->isDead(m_camera); });
}

void GameBase::draw()const
{
	m_tex.map(6000, 8000).draw(m_camera.getDrawPos({ 0,0 }), Alpha(70));

	m_mv.draw(m_camera);

	for (const auto& e : m_EM.m_enemies)
	{
		e->draw(m_camera);
	}

	for (const auto& b : m_myBM.m_ballets)
	{
		b->draw(m_camera);
	}	
}

void GameBase::collisionPlayerWithEnemy()const
{
	if (AnyOf(m_EM.m_enemies, [this](const std::shared_ptr<Enemy>& e){ return e->m_pos.distanceFrom(m_mv.m_pos) < 20; }))
	{
		Println(L"Attacked!");
	}
}