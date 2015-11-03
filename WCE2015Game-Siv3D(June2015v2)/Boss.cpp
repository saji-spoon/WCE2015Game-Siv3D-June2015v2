#include"Boss.hpp"
#include"GameBase.hpp"
#include"Camera.hpp"
#include"AwakePlayerAttack.hpp"
#include"Boss2.hpp"

using namespace shimi;

Boss::Boss(GameBase* gb, const Vec2& pos)
	:m_gb(gb), m_pos(pos){	}

void Boss1::update()
{
	m_state->execute(*this);

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

bool Boss1::isVanished()const
{
	return typeid(m_state) == typeid(state::boss1::Vanish);
}

Boss2::Boss2(GameBase* gb, const Vec2& pos, std::shared_ptr<state::boss2::Boss2Base> state) :Boss(gb, pos), m_state(state)
{

	m_babys = std::vector<Boss2Baby>(3);

	m_bossArea = Obstacle(Point(0, 0), L"Resource/Object/boss2_area.png", 12.0);

	putBaby();
	killBaby();

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

bool Boss2::isVanished()const
{
	return typeid(m_state) == typeid(state::boss2::Vanish);
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
