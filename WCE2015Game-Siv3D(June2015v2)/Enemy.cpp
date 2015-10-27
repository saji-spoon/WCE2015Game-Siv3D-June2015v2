#include"Enemy.hpp"
#include"EnemyManager.hpp"
#include"GameBase.hpp"

using namespace shimi;

Enemy::Enemy(shimi::EnemyManager* manager, const Vec2& pos, const shimi::MyAnime& anime, ShimiColors sColor, const Optional<ItemRecord>& ir = none) :m_manager(manager), m_pos(pos), m_anime(anime), m_shimiColor(sColor)
{
	if (!ir) return;

	m_itemID = m_manager->m_gb->m_idb.Register(ir.value());
}

void Enemy::update()
{
	m_anime.update();

	if (m_manager->m_gb->getMyVehiclePos().distanceFrom(m_pos) >= ConfigParam::DEPOP_DISTANCE)
	{
		++m_depopCount;
	}
	else
	{
		m_depopCount = 0;
	}

	if (m_depopCount >= ConfigParam::DEPOP_COUNT) m_isDead = true;
}

void StopEnemy::moveImpl(boco::coroutine<Enemy*>::pull_type& yield)
{
	for (;;)
	{
		m_shot->update(m_pos, Vec2(0.0, -1.0));

		yield();
	}


	for (;;)
	{
		yield();
	}
}