#pragma once
#include<Siv3D.hpp>
#include"PartAnimation.hpp"
#pragma warning (disable : 4018)

namespace shimi
{

const static String texPath = L"Resource/Boss/Boss1/";

enum class Boss1AnimeMode
{
	Normal,
	Damaged,
	Vanished
};

class Boss1Anime
{
public:
	PTexture m_body = PTexture{ Texture(texPath + L"dou.png"), {0, 0}, {61, 181}, false };
	PTexture m_headUpper;
	PTexture m_headDowner;
	PTexture m_leftBackHand;// = PTexture{ Texture(texPath + L"ushiroashi.png"), {}, { 0, 0 }, false };
	PTexture m_leftMiddleHand;// = PTexture{ Texture(texPath + L"nakaashi.png"), {}, { 0, 0 }, false };
	PTexture m_leftFrontHand;// = PTexture{ Texture(texPath + L"maeashi.png"), {}, { -72, 155 }, false };
	PTexture m_rightBackHand;// = m_leftBackHand.getMirrored();
	PTexture m_rightMiddleHand;// = m_leftMiddleHand.getMirrored();
	PTexture m_rightFrontHand;// = m_leftFrontHand.getMirrored();

	FrameExp<double> m_backRegData;
	FrameExp<double> m_reg1Data;
	FrameExp<double> m_reg2Data;
	FrameExp<int> m_biteData;

	Boss1AnimeMode m_mode = Boss1AnimeMode::Normal;

	Boss1Anime()
	{
		m_backRegData.m_values.push_back({ 3, -Pi / 8.0 });
		m_backRegData.m_values.push_back({ 6, 0.0 });

		m_reg1Data.m_values.push_back({ 3, -Pi / 8.0 });
		m_reg1Data.m_values.push_back({ 6, 0.0 });

		m_reg2Data.m_values.push_back({ 9, 0.0 });
		m_reg2Data.m_values.push_back({ 3, -Pi / 8.0 });
		m_reg2Data.m_values.push_back({ 6, 0.0 });

		m_biteData.m_values.push_back({ 20, 0 });
		m_biteData.m_values.push_back({ 20, 10 });

		m_headUpper = PTexture{ Texture(texPath + L"uwaago.png"), { 0, 0 }, { 65, 31 }, false };
		m_headDowner = PTexture{ Texture(texPath + L"ago.png"), { 0, 0 }, { 63, 0 }, false };

		m_leftBackHand = PTexture{ Texture(texPath + L"ushiroashi.png"), { 0, 0 }, Vec2{ 139, 222 }*0.65, false };
		m_leftMiddleHand = PTexture{ Texture(texPath + L"nakaashi.png"), { 0, 0 }, Vec2{ 253, 145 }*0.65, false };
		m_leftFrontHand = PTexture{ Texture(texPath + L"maeashi.png"), { 0, 0 }, Vec2{ 148, 33 }*0.65, false };

		m_headUpper = Attach(m_body, m_headUpper, Vec2(61, 230));
		m_headDowner = Attach(m_body, m_headDowner, Vec2(61, 263));

		m_leftBackHand = Attach(m_body, m_leftBackHand, Vec2(42, 252)*0.65);
		m_leftMiddleHand = Attach(m_body, m_leftMiddleHand, Vec2(47, 283)*0.65);
		m_leftFrontHand = Attach(m_body, m_leftFrontHand, Vec2(32, 326)*0.65);

		m_rightBackHand = m_leftBackHand.getMirrored();
		m_rightMiddleHand = m_leftMiddleHand.getMirrored();
		m_rightFrontHand = m_leftFrontHand.getMirrored();
	}

	void draw(const Vec2& basePos, const double baseTheta)const 
	{
		if (m_mode == Boss1AnimeMode::Vanished) return;

		Color diffColor = (m_mode == Boss1AnimeMode::Normal) ? Color(255, 255, 255) : Color(255, 120, 120);

		m_body.draw(basePos, baseTheta, Vec2(0, 0), 0, diffColor);

		m_leftBackHand.draw(basePos, baseTheta, Vec2(0, 0), m_backRegData.getData(), diffColor);
		m_rightBackHand.draw(basePos, baseTheta, Vec2(0, 0), m_backRegData.getData(), diffColor);
		m_leftMiddleHand.draw(basePos, baseTheta, Vec2(0, 0), m_reg1Data.getData(), diffColor);
		m_rightMiddleHand.draw(basePos, baseTheta, Vec2(0, 0), m_reg2Data.getData(), diffColor);
		m_leftFrontHand.draw(basePos, baseTheta, Vec2(0, 0), m_reg2Data.getData(), diffColor);
		m_rightFrontHand.draw(basePos, baseTheta, Vec2(0, 0), m_reg1Data.getData(), diffColor);

		m_headDowner.draw(basePos, baseTheta, Vec2(0, m_biteData.getData()), 0, diffColor);
		m_headUpper.draw(basePos, baseTheta, Vec2(0, 0), 0,  diffColor);

	}

	void update()
	{
		m_backRegData.update();
		m_reg1Data.update();
		m_reg2Data.update();
		m_biteData.update();
	}

	void reset()
	{
		m_backRegData.timerReset();
		m_reg1Data.timerReset();
		m_reg2Data.timerReset();
		m_biteData.timerReset();
	}
};

};