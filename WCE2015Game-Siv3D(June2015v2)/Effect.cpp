#include"Effect.hpp"
#include"GameBase.hpp"
#include"EffectManager.hpp"
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

	Circle(drawPos, m_r*rate).drawFrame(7.0, 0.0, ToColor(m_col).setAlpha(TOUINT(0.8*diffuse)));
	Circle(drawPos, m_r*rate).drawFrame(0.0, 7.0, ToColor(m_col).setAlpha(TOUINT(0.4*diffuse)));

	return t < m_limitTime;
}

NotifyStr::NotifyStr(const String& str, const Color& col, int stopTime) :m_str(str), m_col(col), m_stopTime(stopTime)
{
}

void NotifyStr::draw(const Vec2& pos)const
{
	const double vanishTimeRate = Saturate(static_cast<double>(m_timer - m_stopTime) / 30.0);

	FontAsset(L"Notify1").drawCenter(m_str, D2Camera::I()->getDrawPos(pos + m_flow), AlphaF(1.0 - vanishTimeRate)*m_col);
}

void NotifyStr::update()
{
	if (m_timer < m_stopTime)
	{
	}
	else
	{
		m_flow -= Vec2(0, 1.5);
	}

	++m_timer;
}


NotifyStr2::NotifyStr2(const String& str1, const String& str2, const Color& col1, int stopTime, const Color& col2) 
	:m_str1(str1),
	m_str2(str2),
	m_col1(col1),
	m_col2(col2),
	m_stopTime(stopTime),
	m_font(20, L"02‚¤‚Â‚­‚µ–¾’©‘Ì", FontStyle::Outline)
{
	m_font.changeOutlineStyle(TextOutlineStyle(col2, col1, 1.0));
}

void NotifyStr2::draw(const Vec2& pos)const
{
	const double vanishTimeRate = Saturate(static_cast<double>(m_timer - m_stopTime) / 30.0);

	m_font.drawCenter(m_str1, D2Camera::I()->getDrawPos(pos + m_flow), AlphaF(1.0 - vanishTimeRate));
	m_font.drawCenter(m_str2, D2Camera::I()->getDrawPos(pos + Vec2(0, -30) + m_flow), AlphaF(1.0 - vanishTimeRate));
}

void NotifyStr2::update()
{
	if (m_timer < m_stopTime)
	{
	}
	else
	{
		m_flow -= Vec2(0, 1.5);
	}

	++m_timer;
}


ItemGet::ItemGet(GameBase* gb, const Vec2& pos, const ShimiColors& col, int val)
	:m_gb(gb), m_col(col), m_val(val), m_str(L"+" + Format(val), ToColor(col), 15)
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
		Triangle(D2Camera::I()->getDrawPos(p.m_pos), 15).draw(ToColor(m_col).setAlpha(128));
	}

	const Vec2 mvPos = m_gb->getMyVehiclePos();

	for (auto& p : m_particles)
	{
		const Vec2 dir = (mvPos - p.m_pos).normalized();

		p.m_pos += dir*m_speed;

		if (p.m_pos.distanceFrom(mvPos) < 10.0) p.m_isDead = true;
	}

	Erase_if(m_particles, [](const Particle& p){ return p.m_isDead; });
	
	if (m_particles.size() == 0)
	{
		m_str.draw(m_gb->getMyVehiclePos()-Vec2(0, 55));

		m_str.update();
	}

	return t < 10;
}

Notify::Notify(GameBase* gb, const NotifyStr2& notify)
	:m_gb(gb),
	m_str(notify)
{
}

bool Notify::update(double t)
{
	m_str.draw(m_gb->getMyVehiclePos() - Vec2(0, 55));

	m_str.update();

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

	return t < 10;
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

	return t < 10;
}

bool Vanishing::update(double t)
{
	progress += speed;

	double progressRate = Saturate(progress / (1.0*m_size));

	for (int i = 0; i < 6; ++i)
	{
		//Circle(EaseInOut(m_pos, m_pos + Circular0(m_size, 1.0 * i * Pi / 3.0), Easing::Linear, progressRate), (30.0 / 100.0*m_size) * (1.0 - progressRate)).drawFrame(0.0, 6.0, Color(180,180,180));
		//Circle(EaseInOut(m_pos, m_pos + Circular0(m_size, 1.0 * i * Pi / 3.0), Easing::Linear, progressRate), (30.0 / 100.0*m_size) * (1.0 - progressRate)).draw(Palette::White);
		Circle(EaseInOut(m_pos, m_pos + Circular0(m_size, 1.0 * i * Pi / 3.0), Easing::Linear, progressRate), (30.0 / 100.0*m_size) * (1.0 - progressRate)).movedBy(D2Camera::I()->getDrawPos(Vec2(0, 0))).draw(m_col);
		Circle(EaseInOut(m_pos, m_pos + Circular0(m_size*0.6, Pi / 6.0 + 1.0 * i * Pi / 3.0), Easing::Linear, progressRate), 20.0 * (1.0 - progressRate)).movedBy(D2Camera::I()->getDrawPos(Vec2(0, 0))).draw(m_col);
	}

	return t < 10 && progressRate < 1.0;
}

bool VanishingMV::update(double t)
{
	progress += speed;

	double progressRate = Saturate(progress / (1.0*m_size));

	for (int i = 0; i < 6; ++i)
	{
		Circle(EaseInOut(m_pos, m_pos + Circular0(m_size, 1.0 * i * Pi / 3.0), Easing::Linear, progressRate), (30.0 / 100.0*m_size) * (1.0 - progressRate)).movedBy(D2Camera::I()->getDrawPos(Vec2(0,0))).drawFrame(0.0, 6.0, Color(180, 180, 180));
		Circle(EaseInOut(m_pos, m_pos + Circular0(m_size, 1.0 * i * Pi / 3.0), Easing::Linear, progressRate), (30.0 / 100.0*m_size) * (1.0 - progressRate)).movedBy(D2Camera::I()->getDrawPos(Vec2(0, 0))).draw(Palette::White);
		//Circle(EaseInOut(m_pos, m_pos + Circular0(m_size, 1.0 * i * Pi / 3.0), Easing::Linear, progressRate), (30.0 / 100.0*m_size) * (1.0 - progressRate)).draw(m_col);
		//Circle(EaseInOut(m_pos, m_pos + Circular0(m_size*0.6, Pi / 6.0 + 1.0 * i * Pi / 3.0), Easing::Linear, progressRate), 20.0 * (1.0 - progressRate)).draw(m_col);
	}

	return t < 10 && progressRate < 1.0;
}

bool Charging::update(double t)
{
	const int firstLimit = 80;
	const int secondLimit = 20;

	if (m_timer < firstLimit)
	{
		const double progressRate = Saturate(1.0*m_timer / firstLimit);

		Circle(m_pos, 150 * (1.0 - progressRate)).movedBy(D2Camera::I()->getDrawPos(Vec2(0, 0))).drawFrame(3.0, 0.0, Color(120, 120, 120));
	}
	else
	{
		const double progressRate = Saturate(1.0*(m_timer - firstLimit) / secondLimit);

		Circle(m_pos, 80 * progressRate).movedBy(D2Camera::I()->getDrawPos(Vec2(0, 0))).drawFrame(10.0, .0, Color(200, 200, 200, TOUINT((1.0 - progressRate) * 255)));

	}

	++m_timer;

	return t < 10;

}