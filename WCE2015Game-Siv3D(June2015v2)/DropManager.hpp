#pragma once
#include<vector>
#include<Siv3D.hpp>

namespace shimi
{

	struct Drop
	{


		Drop(){}
		Drop(const String& tag, const Vec2& pos, double theta, double scale = 1.0)
			:m_tag(tag),
			m_pos(pos),
			m_theta(theta),
			m_scale(scale)
		{}

		String m_tag;
		Vec2 m_pos;
		double m_theta;
		double m_scale;
	};

	class DropManager
	{
	public:

		static DropManager* I()
		{
			static DropManager instance;
			return &instance;
		}

		DropManager(const DropManager& rhs) = delete;

		DropManager& operator=(const DropManager& rhs) = delete;

		std::vector<Drop> m_drops;

		void draw()const;

	private:
		DropManager(){}


	};

	class ScheduleTimer
	{
	public:
		ScheduleTimer(){}

		ScheduleTimer(const std::vector<int>& schedules)
			:m_schedule(schedules)
		{}

		int m_timer = 0;

		int m_phase = 0;

		std::vector<int> m_schedule;

		bool isDropTime()const;
		void update();
	};

}