#pragma once
#include<Siv3D.hpp>
#include"Obstacle.hpp"
#include"SimpleState.hpp"

namespace shimi
{
class StaffRoll
{
public:
	StaffRoll();

	void draw()const;

	void nextPage();

	bool m_isFinished = false;

	std::vector<String> m_strs;

	TextReader m_reader;

};

class CameraWork
{
public:
	Vec2 m_start;

	Vec2 m_end;

	double m_progress = 0;


	CameraWork()
	{

	}

	double update()
	{
		m_progress += 3.0; //speed

		const double progressRate = m_progress / (m_end - m_start).length();

		const Vec2 newPos = EaseInOut(m_start, m_end, Easing::Linear,progressRate);

		D2Camera::I()->m_pos = newPos;

		return progressRate >= 1.0;
	}

	void reset()
	{
		m_start = RandomVec2(Rect(0, 0, ConfigParam::SIZE_OF_NORMALWORLD));
	
		m_end = RandomVec2(Rect(0, 0, ConfigParam::SIZE_OF_NORMALWORLD));

		m_progress = 0;
	}


};


class Ending
{
public:

	Ending(){}

	Ending(const std::vector<std::shared_ptr<ObstacleBase>>& obs);

	CameraWork m_camera;

	StaffRoll m_staffRoll;

	Texture m_tex = Texture(L"Resource/Paper2.png");

	std::vector<std::shared_ptr<ObstacleBase>> m_obstacles;

	SimpleState m_sceneState;

	int m_fadeTime;

	double m_diffuse = 1.0;

	void draw()const;

	void update();

};
}