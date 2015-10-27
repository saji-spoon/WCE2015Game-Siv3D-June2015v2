#include"ShotGenerator.hpp"
#include"GameBase.hpp"
#include"Camera.hpp"


using namespace shimi;


void BlueShot1Generator::draw(const Vec2& vehiclePos, const Vec2& vehicleV)
{
	Circle(D2Camera::I()->getDrawPos(m_pos), 16).draw(ToColor(ShimiColors::Blue).setAlpha(155));
}

void BlueShot1Generator::generate(const Vec2& vehiclePos, const Vec2& vehicleV)
{
	if (m_waitTimer > 80)
	{
		for (int i = 0; i < 6; ++i)
		{
			m_gb->m_myBM.m_ballets.push_back(std::shared_ptr<Ballet>(new BalletLimit(
				&(m_gb->m_myBM),
				L"blueBallet",
				ShimiColors::Blue,
				m_pos,
				120,
				3.0,
				(60.0*i) / 360.0 * 2.0 * Pi
				)));
		}
		m_waitTimer = 0;
	}

	++m_waitTimer;

}
