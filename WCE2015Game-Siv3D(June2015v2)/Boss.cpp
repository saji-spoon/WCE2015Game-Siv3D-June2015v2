#include"Boss.hpp"
#include"Boss2.hpp"
#include"GameBase.hpp"
#include"Camera.hpp"
#include"AwakePlayerAttack.hpp"


using namespace shimi;

Boss::Boss(GameBase* gb, const Vec2& pos)
	:m_gb(gb), m_pos(pos){	}

void Boss1::update()
{
	m_state->execute(*this);

	if (m_isDead) return;

	AwakeEnemyAttack(m_gb, getMyCollision(m_pos), ShimiColors::Red, 1);
}

void Boss1::setVtoMV()
{
	const Vec2 tar = m_gb->getMyVehiclePos();

	m_v = (tar - m_pos).normalized()*6.0;
}

void Boss1::draw()const
{
	assert(m_v.length() != 0);

	m_anime.draw(D2Camera::I()->getDrawPos(m_pos), Circular6(m_v).theta);

}

void Boss1::debugDraw()const
{
#ifdef _DEBUG
	getBossArea().movedBy(D2Camera::I()->getDrawPos(Vec2(0, 0)).asPoint()).draw(Alpha(128) * Palette::Red);
#endif

}

bool Boss1::run()
{
	Vec2 futurePos = m_pos + m_v;

	bool isCrashed = m_gb->collisionSomethingWithObstacle(getMyCollision(futurePos)) || !getMyCollision(futurePos).intersects(getBossArea());

	if (isCrashed)
	{
		return false;
	}

	m_pos = futurePos;

	return true;
}

void Boss1::checkMyVehicleAway()
{
	if (!isInBossBattle())
	{
		changeState(std::shared_ptr<state::boss1::Boss1Base>(new state::boss1::Stay()));
	}
}

bool Boss1::isInBossBattle()const
{
	return getBossArea().intersects(m_gb->getMyVehiclePos());
}

void Boss1::killedSilent()
{
	m_damagable = false;

	m_anime.m_mode = Boss1AnimeMode::Vanished;

	m_isDead = true;
}

Boss2::Boss2(GameBase* gb, const Vec2& pos, std::shared_ptr<state::boss2::Boss2Base> state) :Boss(gb, pos), m_state(state)
{

	m_babys = std::vector<Boss2Baby>(3);

	m_bossArea = Obstacle(Point(0, 0), L"Resource/Object/boss2_area.png", 12.0);

	putBaby();
	killBaby();

#ifdef _DEBUG
	m_life = 0;
	m_state = std::shared_ptr<state::boss2::Boss2Base>(new state::boss2::Damagable());
#endif
}

void Boss2::draw()const
{

	m_anime.draw(D2Camera::I()->getDrawPos(m_pos), 0);

	if (m_barrier) drawBarrier();

	for (const auto& baby : m_babys)
	{
		baby.draw();
	}
}

void Boss2::update()
{
	m_state->execute(*this);

	if (m_isDead) return;

	AwakeEnemyAttack(m_gb, getMyCollision(m_pos), ShimiColors::Orange, 1);
}

void Boss2::debugDraw()const
{
#ifdef _DEBUG
	m_bossArea.m_pols.drawFrame(D2Camera::I()->getDrawPos(Vec2(0, 0)),3.0, Alpha(128) * Palette::Red);
#endif

}

bool Boss2::isInBossBattle()const
{
	return m_bossArea.m_pols.intersects(Circle(m_gb->getMyVehiclePos(), 10));
}

void Boss2::putBaby()
{

	m_babys[0] = Boss2Baby(m_pos, m_pos + Vec2(-304, 195),
		std::shared_ptr<EnemyShot>(new StraightShot(m_gb, { { Vec2(0, -1), 120 }, { Vec2(0, 1), 0 }, { Vec2(1, 0), 0 }, { Vec2(-1, 0), 0 } },
		BalletAVR(&(m_gb->m_enemyBM),
		L"enemyBallet1",
		ShimiColors::Orange,
		Vec2(0, 0)),
		true)));

	m_babys[1] = Boss2Baby(m_pos, m_pos + Vec2(0, 395),
		std::shared_ptr<EnemyShot>(new StraightShot(m_gb, { { Vec2(0, -1), 120 }, { Vec2(0, 1), 0 }, { Vec2(1, 0), 0 }, { Vec2(-1, 0), 0 } },
		BalletAVR(&(m_gb->m_enemyBM),
		L"enemyBallet1",
		ShimiColors::Orange,
		Vec2(0, 0)),
		true)));

	m_babys[2] = Boss2Baby(m_pos, m_pos + Vec2(304, 195),
		std::shared_ptr<EnemyShot>(new StraightShot(m_gb, { { Vec2(0, -1), 120 }, { Vec2(0, 1), 0 }, { Vec2(1, 0), 0 }, { Vec2(-1, 0), 0 } },
		BalletAVR(&(m_gb->m_enemyBM),
		L"enemyBallet1",
		ShimiColors::Orange,
		Vec2(0, 0)),
		true)));

}

void Boss2::drawBarrier()const
{
	Circle(D2Camera::I()->getDrawPos( m_pos), 200).drawFrame(0, 5.0, ToColor(ShimiColors::Orange));
	Circle(D2Camera::I()->getDrawPos(m_pos), 200).draw(Alpha(80) * ToColor(ShimiColors::Orange));
}

void Boss2::killedSilent()
{
	m_damagable = false;

	m_isDead = true;

	m_anime.m_mode = Boss2AnimeMode::Vanished;
}
