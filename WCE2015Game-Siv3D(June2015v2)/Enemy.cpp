#include"Enemy.hpp"
#include"EnemyManager.hpp"
#include"GameBase.hpp"

using namespace shimi;

Enemy::Enemy(EnemyManager* manager,
	const Vec2& pos,
	const shimi::MyAnime& anime,
	const std::shared_ptr<EnemyShot> enemyShot,
	ShimiColors sColor) :m_manager(manager), m_pos(pos), m_anime(anime), m_shot(enemyShot), m_shimiColor(sColor)
{
	/*
	if (!ir) return;

	m_itemID = m_manager->m_gb->m_idb.Register(ir.value());
	*/
}

void Enemy::update()
{
	m_anime.update();

	move();
	
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

void StopEnemy::move()
{
	m_shot->update(m_pos, Vec2(0.0, -1.0));
}

StraightEnemy::StraightEnemy(EnemyManager* manager,
	std::initializer_list<Vec2> list,
	double speed,
	const shimi::MyAnime& anime,
	const std::shared_ptr<EnemyShot> enemyShot,
	const ShimiColors& sColor,
	bool rotatable,
	bool loop) :
	Enemy(
	manager,
	Vec2(0, 0),
	anime,
	enemyShot,
	sColor),
	m_poss(list),
	m_speed(speed),
	m_rotatable(rotatable),
	m_loop(loop)
{
	if (m_poss.size() < 2)
	{
		LOG_ERROR(L"LineEnemy: 地点表がないか、大きさが1です");
		m_poss.push_back(Vec2(0, 0));
		m_poss.push_back(Vec2(1, 0));

	}
	setPath(m_poss[0], m_poss[1]);
	m_pos = m_poss[0];
	m_progress = 0;
}

StraightEnemy::StraightEnemy(EnemyManager* manager,
	std::vector<Vec2>& poss,
	double speed,
	const shimi::MyAnime& anime,
	const std::shared_ptr<EnemyShot> enemyShot,
	const ShimiColors& sColor,
	bool rotatable,
	bool loop) :
	Enemy(
	manager,
	Vec2(0, 0),
	anime,
	enemyShot,
	sColor
	),
	m_poss(poss),
	m_speed(speed),
	m_rotatable(rotatable),
	m_loop(loop)
{
	if (m_poss.size() < 2)
	{
		LOG_ERROR(L"LineEnemy: 地点表がないか、大きさが1です");
		m_poss[0] = Vec2(0, 0);
		m_poss[1] = Vec2(0, 0);

	}
	setPath(m_poss[0], m_poss[1]);
	m_pos = m_poss[0];
	m_progress = 0;
}



void StraightEnemy::move()
{
	m_shot->update(m_pos, m_speed * (m_start - m_end).normalized());

	if (m_isFinish)return;

	m_progress += m_speed;

	const double progress0To1 = ((m_end - m_start).length() != 0) ? Saturate(m_progress / (m_end - m_start).length()) : 1.0;

	m_pos = EaseInOut(m_start, m_end, Easing::Linear, progress0To1);

	if (progress0To1 == 1.0)
	{
		if (!m_loop) m_isFinish = true;

		const Vec2 nextStart = m_poss[m_phase];

		m_phase += m_indexDir;

		if (m_phase < 0 || m_phase >= m_poss.size())
		{
			//過ぎた時点で反転
			m_phase -= m_indexDir*2;
			m_indexDir *= -1;
		}
		
		const Vec2 nextEnd = m_poss[m_phase];

		setPath(nextStart, nextEnd);
	}

	m_preDir = (m_end - m_start).length() != 0 ? Circular0(m_end - m_start).theta : m_preDir;

}

void StraightEnemy::setPath(const Vec2& start, const Vec2& end)
{
	m_start = start;
	m_end = end;
	m_progress = 0;
}


void StraightEnemy::draw()const
{
	if (m_rotatable)
	{
		m_anime.rotate(m_preDir).drawAt(D2Camera::I()->getDrawPos(m_pos));
	}
	else
	{
		m_anime.drawAt(D2Camera::I()->getDrawPos(m_pos));
	}

}