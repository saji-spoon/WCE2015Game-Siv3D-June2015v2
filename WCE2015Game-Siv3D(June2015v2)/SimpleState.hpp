#pragma once
#include<Siv3D.hpp>

struct SimpleState
{
	SimpleState(){}
	SimpleState(int firstLimit) :m_stateLimit(firstLimit)
	{}

	void update()
	{
		++m_timer;
		++m_allTimer;
	}

	bool isFinished()
	{
		return m_timer >= m_stateLimit;
	}

	void checkTimerAndGoState0(int newLimit)
	{
		if (isFinished())
		{
			m_state = 0;
			m_timer = 0;
			m_stateLimit = newLimit;
		}
	}


	void checkTimerAndGoNextState(int newLimit)
	{
		if (isFinished())
		{
			nextState(newLimit);
		}
	}

	void nextState(int newLimit)
	{
		++m_state;
		m_timer = 0;
		m_stateLimit = newLimit;
	}

	void reset(int newLimit)
	{
		m_state = 0;
		m_timer = 0;
		m_stateLimit = newLimit;
		m_allTimer = 0;
	}

	int m_state = 0;
	int m_timer = 0;
	int m_stateLimit;
	int m_allTimer = 0;
};