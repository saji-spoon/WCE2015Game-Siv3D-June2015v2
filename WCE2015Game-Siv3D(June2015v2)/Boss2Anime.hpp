#pragma once
#include<Siv3D.hpp>
#include"PartAnimation.hpp"

const static String texPath2 = L"Resource/Boss/Boss2/";

namespace shimi
{

enum class Boss2AnimeMode
{
	Normal,
	Damaged,
	Open,
	Vanished
};


class Boss2Anime
{
public:
	PTexture m_body = PTexture{ Texture(texPath2 + L"body_1.png"), { 0, 0 }, { 75, 104 }, false };
	PTexture m_headUpper;
	PTexture m_headDowner;
	PTexture m_leftCover;// = PTexture{ Texture(texPath2 + L"ushiroashi.png"), {}, { 0, 0 }, false };
	PTexture m_leftArm;// = PTexture{ Texture(texPath2 + L"ushiroashi.png"), {}, { 0, 0 }, false };
	PTexture m_leftWing;// = PTexture{ Texture(texPath2 + L"ushiroashi.png"), {}, { 0, 0 }, false };
	PTexture m_rightCover;// = PTexture{ Texture(texPath2 + L"ushiroashi.png"), {}, { 0, 0 }, false };
	PTexture m_rightArm;// = PTexture{ Texture(texPath2 + L"ushiroashi.png"), {}, { 0, 0 }, false };
	PTexture m_rightWing;// = PTexture{ Texture(texPath2 + L"ushiroashi.png"), {}, { 0, 0 }, false };
	PTexture m_belly;// = PTexture{ Texture(texPath2 + L"ushiroashi.png"), {}, { 0, 0 }, false };

	FrameExp<double> m_wingData;
	FrameExp<double> m_armData;
	FrameExp<int> m_biteData;

	Boss2AnimeMode m_mode = Boss2AnimeMode::Normal;

	Boss2Anime()
	{
		m_wingData.m_values.push_back({ 2, -Pi / 8.0 });
		m_wingData.m_values.push_back({ 2, 0.0 });

		m_armData.m_values.push_back({ 20, -Pi / 8.0 });
		m_armData.m_values.push_back({ 60, 0.0 });

		m_biteData.m_values.push_back({80, 0});
		m_biteData.m_values.push_back({ 80, 10 });

		m_headUpper = PTexture{ Texture(texPath2 + L"head_1.png"), { 0, 0 }, { 81, 68 }, false };
		m_headDowner = PTexture{ Texture(texPath2 + L"bite_1.png"), { 0, 0 }, { 32, 10 }, false };

		m_leftCover = PTexture{ Texture(texPath2 + L"cover_1.png"), { 0, 0 }, Vec2{ 70, 7 }, false };
		m_leftArm = PTexture{ Texture(texPath2 + L"arm_1.png"), { 0, 0 }, Vec2{ 145, 182 }, false };
		m_leftWing = PTexture{ Texture(texPath2 + L"wing_1.png"), { 0, 0 }, Vec2{ 125, 72 }, false };

		m_belly = PTexture{ Texture(texPath2 + L"belly_1.png"), { 0, 0 }, Vec2{ 73, 155 }, false };

		m_headUpper = Attach(m_body, m_headUpper , Vec2(75, 180));
		m_headDowner = Attach(m_headUpper, m_headDowner, Vec2(82,73));

		m_leftCover = Attach(m_headUpper, m_leftCover, Vec2(61, 3));
		m_leftArm = Attach(m_body, m_leftArm, Vec2(12, 110));
		m_leftWing = Attach(m_body, m_leftWing, Vec2(70,21));

		m_belly = Attach(m_body, m_belly, Vec2(75, 36));

		m_rightCover = m_leftCover.getMirrored();
		m_rightArm = m_leftArm.getMirrored();
		m_rightWing = m_leftWing.getMirrored();
	}

	void draw(const Vec2& basePos, const double baseTheta)const
	{
		if (m_mode == Boss2AnimeMode::Vanished) return;

		Color diffColor = (m_mode == Boss2AnimeMode::Normal) ? Color(255, 255, 255) : Color(255, 120, 120);
		m_belly.draw(basePos, baseTheta, Vec2(0, 0), 0, diffColor);
		m_rightWing.draw(basePos, baseTheta, Vec2(0, 0), m_wingData.getData(), diffColor);
		m_leftWing.draw(basePos, baseTheta, Vec2(0, 0), m_wingData.getData(), diffColor);
		m_leftArm.draw(basePos, baseTheta, Vec2(0, 0), 0 + m_armData.getData(), diffColor);
		m_rightArm.draw(basePos, baseTheta, Vec2(0, 0), m_armData.getData(), diffColor);
		m_body.draw(basePos, baseTheta, Vec2(0, 0), 0, diffColor);
		m_headDowner.draw(basePos, baseTheta, Vec2(0, 0) + Vec2(0, m_biteData.getData()), 0, diffColor);
		m_headUpper.draw(basePos, baseTheta, Vec2(0, 0), 0, diffColor);

		if (m_mode == Boss2AnimeMode::Open)
		{
			m_rightCover.draw(basePos, baseTheta, Vec2(0, 0), -Pi*3.0 / 2.0, diffColor);
			m_leftCover.draw(basePos, baseTheta, Vec2(0, 0), -Pi*3.0 / 2.0, diffColor);
		} 
		else
		{
			m_rightCover.draw(basePos, baseTheta, Vec2(0, 0), 0, diffColor);
			m_leftCover.draw(basePos, baseTheta, Vec2(0, 0), 0, diffColor);
		}

	}

	void update()
	{
		m_wingData.update();
		m_biteData.update();
		m_armData.update();
	}

	void reset()
	{
		m_wingData.timerReset();
		m_biteData.timerReset();
		m_armData.timerReset();
	}
};
}