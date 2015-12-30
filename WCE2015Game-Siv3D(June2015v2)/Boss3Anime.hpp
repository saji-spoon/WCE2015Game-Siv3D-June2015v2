#pragma once
#include<Siv3D.hpp>
#include"PartAnimation.hpp"

const static String texPath3 = L"Resource/Boss/Boss3/";

namespace shimi
{

	enum class Boss3AnimeMode
	{
		Normal,
		Damagable,
		Damaged,
		Vanished
	};


	class Boss3Anime
	{
	public:
		PTexture m_body = PTexture{ Texture(texPath3 + L"fish_mini.png"), { 0, 0 }, { 172, 450 }, false };

		Boss3AnimeMode m_mode = Boss3AnimeMode::Normal;

		Boss3Anime()
		{

		}

		void draw(const Vec2& basePos, const double baseTheta)const
		{
			if (m_mode == Boss3AnimeMode::Vanished) return;

			Color diffColor = (m_mode != Boss3AnimeMode::Damaged) ? Color(255, 255, 255) : Color(255, 120, 120);

			m_body.draw(basePos, baseTheta, Vec2(0, 0), 0, diffColor);

		}

		void update()
		{
		}

		void reset()
		{
		}
	};
}