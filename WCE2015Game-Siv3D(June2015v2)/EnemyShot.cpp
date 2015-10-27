#include"EnemyShot.hpp"
#include"GameBase.hpp"

using namespace shimi;

void StraightShot::update(const Vec2& pos, const Vec2& v)
{
	//����v�͎g��Ȃ��i�{�̂̌����ɂ�����炸�X�P�W���[���ɐݒ肳�ꂽdir�̒ʂ�ɔ��˂���j

	if (m_phase >= m_schedule.size())
	{
		if (m_loop) reset();
		else return;
	}

	if (m_timer >= m_schedule[m_phase].delay)
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