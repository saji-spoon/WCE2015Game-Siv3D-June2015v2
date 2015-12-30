#pragma once
#include<Siv3D.hpp>
#include"SimpleState.hpp"


namespace shimi
{
class GameBase;

class SavePoint
{
public:

	GameBase* m_gb;

	Vec2 m_nowRecoverPos = Vec2(646, 5862);

	//savePoint‚ÉG‚ê‚é‚Ì‚ª–³Œø‚ÌŠÔ
	int m_timer = 130;

	SimpleState m_animeState;

	std::vector<Vec2> m_savePoints;

	SavePoint(GameBase* gb);

	Vec2 getRecoverPoint()
	{
		return m_nowRecoverPos;
	}

	void draw()const;

	void update();

	bool collisionSavePoint(const Vec2& mvPos);

	void setTimer(int value);

};
}