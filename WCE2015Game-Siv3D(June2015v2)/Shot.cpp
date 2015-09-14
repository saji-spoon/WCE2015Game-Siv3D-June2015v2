#include"Shot.hpp"
#include"GameBase.hpp"

using namespace shimi;

void RedShot1::draw()const
{
	const Vec2 pos = D2Camera::I()->getDrawPos(m_gb->m_mv.m_pos);
	const Vec2 v = m_gb->m_mv.m_v;

	//‰ñ“]Žx“_
	const Vec2 rotPos = Vec2(0, 50);
	const Vec2 rotPosMir = Vec2{ (m_tex.size.x - rotPos.x), rotPos.y };
	//Ž©‹@’†S‚©‚ç‚Ì‚¸‚ê
	const Vec2 relPos = Vec2(20, 0);
	//‰ñ“]
	const double theta = Circular(v).theta;

	const Vec2 posD = pos + relPos.rotated(theta) - rotPos;
	m_tex.rotateAt(rotPos, theta).draw(posD);
	const Vec2 posDmir = pos + (-relPos).rotated(theta) - rotPosMir;
	m_tex.mirror().rotateAt(rotPosMir, theta).draw(posDmir);
}

void RedShot1::drawFrame()const
{
	//ƒVƒ‡ƒbƒg‘I‘ðŽž‚ÌƒtƒŒ[ƒ€•`‰æ
	const Vec2 pos = D2Camera::I()->getDrawPos(m_gb->m_mv.m_pos);
	const Vec2 v = m_gb->m_mv.m_v;

	const Vec2 relPos = Vec2(0, -40);
	const double theta = Circular(v).theta;

	const Vec2 posD = pos + relPos.rotated(theta);
	Circle(posD, 10).drawFrame(4.0, 0.0, Color(224, 0, 0, 128));
}

void RedShot1::shot()
{
	if (m_count > 0) return;

	for (int i = 0; i < 3; ++i)
	{
		m_gb->m_myBM.m_ballets.push_back(std::shared_ptr<Ballet>(new BalletAVR(
			&(m_gb->m_myBM),
			L"ballet3",
			m_gb->getMyVehiclePos(),
			5.00,
			Circular3(m_gb->m_mv.m_v).theta + (i - 1) * Pi / 36.0,
			0.0,
			0.0)));
	}

	m_count = m_interval;
}


void BlueShot1::draw()const
{
	const Vec2 pos = D2Camera::I()->getDrawPos(m_gb->m_mv.m_pos);
	const Vec2 v = m_gb->m_mv.m_v;

	//‰ñ“]Žx“_
	const Vec2 rotPos = Vec2(22, 14);
	//Ž©‹@’†S‚©‚ç‚Ì‚¸‚ê
	const Vec2 relPos = Vec2(0, 50);
	//‰ñ“]
	const double theta = Circular(v).theta;

	const Vec2 posD = pos + relPos.rotated(theta) - rotPos;
	m_tex.rotateAt(rotPos, theta).draw(posD);
}

void BlueShot1::drawFrame()const
{
	const Vec2 pos = D2Camera::I()->getDrawPos(m_gb->m_mv.m_pos);
	const Vec2 v = m_gb->m_mv.m_v;

	const Vec2 relPos = Vec2(0, -40);
	const double theta = Circular(v).theta;

	const Vec2 posD = pos + relPos.rotated(theta);
	Circle(posD, 10).drawFrame(4.0, 0.0, Color(55, 122, 238, 128));
}


void BlueShot1::shot()
{
	if (m_count > 0) return;

	for (int i = 0; i < 3; ++i)
	{
		m_gb->m_myBM.m_ballets.push_back(std::shared_ptr<Ballet>(new BalletAVR(
			&(m_gb->m_myBM),
			L"ballet3",
			m_gb->getMyVehiclePos(),
			5.00,
			Circular3(m_gb->m_mv.m_v).theta + (i - 1) * Pi / 36.0,
			0.0,
			0.0)));
	}

	m_count = m_interval;
}



void WhiteShot::shot()
{
	if (m_count > 0) return;

	
	m_gb->m_myBM.m_ballets.push_back(std::shared_ptr<Ballet>(new BalletAVR(
		&(m_gb->m_myBM),
		L"ballet3",
		m_gb->getMyVehiclePos(),
		5.00,
		Circular3(m_gb->m_mv.m_v).theta,
		0.0,
		0.0)));

	m_count = m_interval;
}