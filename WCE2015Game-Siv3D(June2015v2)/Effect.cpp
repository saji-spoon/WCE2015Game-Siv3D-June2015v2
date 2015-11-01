#include"Effect.hpp"
#include"GameBase.hpp"
using namespace shimi;

bool VanishingBallet::update(double t)
{
	const double rate = t / m_limitTime;

	const Vec2 drawPos = D2Camera::I()->getDrawPos(m_pos);

	const double diffuse = 255.0 * Saturate((1.0 - rate));

	Circle(drawPos, m_r*(1.0 - rate)).draw(Color(158, 158, 158, static_cast<s3d::uint32>(diffuse)));

	return t < m_limitTime;
}

bool VanishingEnemy::update(double t) 
{
	const double rate = t / m_limitTime;

	const Vec2 drawPos = D2Camera::I()->getDrawPos(m_pos);

	const double diffuse = 255.0 * Saturate((1.0 - rate));

	Circle(drawPos, m_r*rate).drawFrame(7.0, 0.0, ToColor(ShimiColors::Red).setAlpha(TOUINT(0.8*diffuse)));
	Circle(drawPos, m_r*rate).drawFrame(0.0, 7.0, ToColor(ShimiColors::Red).setAlpha(TOUINT(0.4*diffuse)));

	return t < m_limitTime;
}

ItemGet::ItemGet(GameBase* gb, const Vec2& pos)
	:m_gb(gb)
{
	for (int i = 0; i < 6; ++i)
	{
		m_particles.push_back(Particle{ Vec2(pos + Vec2(0.0, 20.0).rotated(Pi / 3.0 * i)), false });
	}
}

bool ItemGet::update(double t) 
{
	for (const auto& p : m_particles)
	{
		Circle(D2Camera::I()->getDrawPos(p.m_pos), 10).draw(ToColor(ShimiColors::Red).setAlpha(128));
	}

	const Vec2 mvPos = m_gb->getMyVehiclePos();

	for (auto& p : m_particles)
	{
		const Vec2 dir = (mvPos - p.m_pos).normalized();

		p.m_pos += dir*m_speed;

		if (p.m_pos.distanceFrom(mvPos) < 10.0) p.m_isDead = true;
	}

	Erase_if(m_particles, [](const Particle& p){ return p.m_isDead; });

	return t < 10;
}

bool BossWarp::update(double t)

{
	const double end = m_size;
	const Color col = Color(50, 50, 50);

	const Vec2 DrawPos = D2Camera::I()->getDrawPos(m_pos);

	switch (m_s.m_state)
	{
	case 0:
		Circle(DrawPos, Lerp(0.0, end, EaseOut(Easing::Quart, 1.0 * m_s.m_timer / (1.0 * m_s.m_stateLimit)))).draw(col);

		m_s.checkTimerAndGoNextState(20);

		break;
	case 1:
		Circle(DrawPos, Lerp(0.0, end, EaseInOut(Easing::Quart, 1.0))).draw(col);

		m_s.checkTimerAndGoNextState(20);

		break;
	case 2:
		Circle(DrawPos, Lerp(end, 0.0, EaseIn(Easing::Quart, 1.0 * m_s.m_timer / m_s.m_stateLimit))).draw(col);

		m_s.checkTimerAndGoNextState(20);
	default:
		break;
	}

	for (const auto& p : m_particles)
	{
		Circle(D2Camera::I()->getDrawPos(p.m_pos), 10).draw(col);
	}

	for (auto& p : m_particles)
	{
		p.update();
	}

	Erase_if(m_particles, [](const TimedParticle& p){ return p.isDead();  });

	if (m_s.m_timer % 5 == 0 && m_s.m_state > 0 && m_s.m_state < 3)
	{
		const int particleNum = static_cast<int>(m_size / 1.5);

		for (int i = 0; i < particleNum; ++i)
		{
			const Vec2 dir = RandomVec2(Random(0.0, m_size));

			m_particles.push_back(TimedParticle(m_pos + dir, 10, dir.normalized()*2.0));
		}
	}

	m_s.update();

	return true;
}

bool BossVanish::update(double t) 
{
	const Color col = Color(20, 20, 20, 180);

	const Vec2 DrawPos = D2Camera::I()->getDrawPos(m_pos);

	switch (m_s.m_state)
	{
	case 0:
		Circle(DrawPos, m_easing.easeOut()).draw(col);
		Circle(DrawPos, m_easing.easeOut()*0.8).draw(col);
		Circle(DrawPos, m_easing.easeOut()*0.6).draw(col);

		break;

		break;
	default:
		break;
	}

	for (const auto& p : m_particles)
	{
		Circle(D2Camera::I()->getDrawPos(p.m_pos), 16).draw(col);
	}

	for (auto& p : m_particles)
	{
		p.update();
	}

	Erase_if(m_particles, [](const TimedParticle& p){ return p.isDead();  });

	m_s.update();

	return true;
}