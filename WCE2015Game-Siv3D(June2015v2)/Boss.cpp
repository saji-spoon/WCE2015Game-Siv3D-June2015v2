#include"Boss.hpp"
#include"GameBase.hpp"
#include"Camera.hpp"
#include"AwakePlayerAttack.hpp"

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
	getBossArea().draw(Alpha(128) * Palette::Red);
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
