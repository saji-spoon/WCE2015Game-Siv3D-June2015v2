#include"Enemy.hpp"
#include"EnemyManager.hpp"
#include"GameBase.hpp"
using namespace shimi;

Enemy::Enemy(EnemyManager* em, const Vec2 pos, const Anime& anime, const Optional<ItemRecord> ir)
	:m_manager(em), 
	Entity(pos), 
	m_anime(anime)
{
	if (ir)
	{
		m_itemID = m_manager->m_gb->m_idb.Register(ir.value());
	}
}