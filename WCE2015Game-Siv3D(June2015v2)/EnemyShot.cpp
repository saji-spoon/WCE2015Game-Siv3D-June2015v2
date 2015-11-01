#include"EnemyShot.hpp"
#include"GameBase.hpp"

using namespace shimi;

void StraightShot::update(const Vec2& pos, const Vec2& v)
{
	//今回vは使わない（本体の向きにかかわらずスケジュールに設定されたdirの通りに発射する）

	if (m_phase >= m_schedule.size())
	{
		if (m_loop) reset();
		else return;
	}

	//m_timerが0のphaseは連続発射
	for (; !(m_phase >= m_schedule.size()) && m_timer >= m_schedule[m_phase].delay;)
	{
		shot(pos, m_schedule[m_phase].speed);
		nextPhase();
	}

	++m_timer;
}

void StraightShot::shot(const Vec2& pos, const Vec2& dir)
{
	m_gb->m_enemyBM.m_ballets.push_back(std::shared_ptr<Ballet>(new BalletAVR(
		&(m_gb->m_enemyBM),
		m_copiedBallet.m_balletPictureLabel,
		m_copiedBallet.m_shimiColor,
		pos,
		dir.length(),
		Circular3(dir).theta,
		0.0,
		0.0)));
}

void MVAimShot::update(const Vec2& pos, const Vec2& v)
{
	//今回vは使わない（本体の向きにかかわらずスケジュールに設定されたdirの通りに発射する）

	if (m_phase >= m_schedule.size())
	{
		if (m_loop) reset();
		else return;
	}

	if (m_timer >= m_schedule[m_phase].delay)
	{
		shot(pos, m_schedule[m_phase].SectorDegree, m_schedule[m_phase].speed, m_schedule[m_phase].num);
		nextPhase();
	}

	++m_timer;
}

void MVAimShot::shot(const Vec2& pos, double dosuu, double speed, int num)
{
	const Vec2 BaseDir = (m_gb->getMyVehiclePos() - pos).normalized();

	const double theta = dosuu / 360.0 * 2 * Pi;

	const double thetaBetweenBallet = theta / static_cast<double>(num - 1);

	for (int i = 0; i < num; ++i)
	{
		m_gb->m_enemyBM.m_ballets.push_back(std::shared_ptr<Ballet>(new BalletAVR(
			&(m_gb->m_enemyBM),
			m_copiedBallet.m_balletPictureLabel,
			m_copiedBallet.m_shimiColor,
			pos,
			speed,
			Circular3(BaseDir).theta - theta / 2.0 + thetaBetweenBallet*i,
			0.0,
			0.0)));
	}

}