#pragma once
#include<Siv3D.hpp>
#include"Camera.hpp"

namespace shimi
{
	class Hole
	{
	public:

		Vec2 m_pos = Vec2(3994, 3492);

		double m_start = 170.0;
		double m_end = 190.0;

		double m_progress = 0.0;

		double m_speed = 0.008;

		void draw()const
		{
			Circle(D2Camera::I()->getDrawPos(m_pos), EaseInOut(m_start, m_end, Easing::Cubic, m_progress)).draw(Color(60, 60, 60));
		}

		void update()
		{
			if (m_progress == 1.0)
			{
				std::swap(m_start, m_end);
				m_progress = 0.0;
			}

			m_progress = Saturate(m_progress + m_speed);
		}
	};
}