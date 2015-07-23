#include "GameBase.hpp"

using namespace shimi;

GameBase::GameBase() :
	m_camera(mv.m_pos),
	m_image(Image({ 4000, 3000 }, Palette::White)),
	m_dTex(DynamicTexture(m_image))
{
	/*for prototype*/

	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy( &m_EM, { 1450.0, 2250.0 }, Anime( TextureAsset(L"enemy1"), 4, 1 ) )));
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy( &m_EM, { 1550.0, 2300.0 }, Anime(TextureAsset(L"enemy1"), 4, 1))));
	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(&m_EM, { 1300.0, 2400.0 }, Anime(TextureAsset(L"enemy1"), 4, 1))));

	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(
		&m_EM, { 1700.0, 2300.0 }, Anime(TextureAsset(L"enemy2"), 13, 3
		))));

	m_EM.m_enemies.push_back(std::shared_ptr<Enemy>(new Enemy(
		&m_EM, { 1650.0, 2450.0 }, Anime(TextureAsset(L"enemy2"), 13, 3
		))));
}

void GameBase::update()
{
	updateCamera(mv.m_pos);

	mv.update();

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
			b->drop(m_image);
			//b.m_image.write(m_image, b.m_pos);
		}

		m_dTex.fill(m_image);
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
	m_dTex.draw(m_camera.getDrawPos({ 0, 0 }));

	mv.draw(m_camera);

	for (auto& e : m_EM.m_enemies)
	{
		e->draw(m_camera);
	}

	for (const auto& b : m_myBM.m_ballets)
	{
		b->draw(m_camera);
	}	
}