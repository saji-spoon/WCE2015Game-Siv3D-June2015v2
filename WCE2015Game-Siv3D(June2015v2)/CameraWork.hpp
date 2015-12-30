#pragma once
#include<Siv3D.hpp>
#include"SimpleState.hpp"
#include"Camera.hpp"

namespace shimi
{
struct CameraWork2
{
	SimpleState m_state;
	Vec2 m_startPos;

	CameraWork2() :m_state(60)
	{
		init();
	}

	void init()
	{
		m_startPos = D2Camera::I()->m_pos;
	}

	void update()
	{
		const double progressRate = Saturate(1.0*m_state.m_timer / (1.0*m_state.m_stateLimit));

		const Vec2 focusPos = Vec2(3904, 4082);

		switch (m_state.m_state)
		{
		case 0:
			D2Camera::I()->m_pos = EaseInOut(m_startPos, focusPos, Easing::Cubic, progressRate);

			m_state.checkTimerAndGoNextState(150);
			break;
		case 1:
			D2Camera::I()->m_pos = focusPos;

			m_state.checkTimerAndGoNextState(60);
			break;
		case 2:
			D2Camera::I()->m_pos = EaseInOut(focusPos, m_startPos, Easing::Cubic, progressRate);

			m_state.checkTimerAndGoNextState(60);
			break;
		case 3:
			break;
		}

		m_state.update();

	}
	bool isFinished()
	{
		return m_state.m_state == 3;
	}

};

};