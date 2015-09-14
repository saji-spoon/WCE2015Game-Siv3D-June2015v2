#include"EnemyManager.hpp"
#include"GameBase.hpp"


void shimi::EnemyManager::pop()
{
	const Vec2 myPos = m_gb->getMyVehiclePos();

	for (auto& record : m_enemyDatabase)
	{
		const double dist = record.m_data.m_enemy->m_pos.distanceFrom(myPos);

		if (!record.m_isPop &&
			dist <= ConfigParam::POP_DISTANCE_OUT &&
			ConfigParam::POP_DISTANCE_IN <= dist
			)
		{
			m_enemies.push_back(record.m_data);
			record.m_isPop = true;
		}
	}
}

void shimi::EnemyManager::popForce(const Vec2& center, double r)
{
	for (auto& record : m_enemyDatabase)
	{
		const double dist = record.m_data.m_enemy->m_pos.distanceFrom(center);

		if (!record.m_isPop &&
			dist <= r
			)
		{
			m_enemies.push_back(record.m_data);
			record.m_isPop = true;
		}
	}

}