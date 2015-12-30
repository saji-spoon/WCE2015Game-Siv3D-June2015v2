#pragma once
#include<Siv3D.hpp>
#include"PartAnimation.hpp"
#include"ShimiColors.hpp"

const static String texPath4 = L"Resource/Boss/Boss4/";

namespace shimi
{

	enum class Boss4AnimeMode
	{
		Normal,
		Damagable,
		Damaged,
		Vanished
	};


	class Boss4Anime
	{
	public:
		PTexture m_body = PTexture{ Texture(texPath4 + L"body_1.png"), { 0, 0 }, { 193, 177 }, false };
		PTexture m_red;
		PTexture m_orange;
		PTexture m_green;
		PTexture m_blue;
		PTexture m_purple;

		Boss4AnimeMode m_mode = Boss4AnimeMode::Normal;

		ShimiColors m_col;

		Boss4Anime()
		{
			m_red = PTexture{ Texture(texPath4 + L"head_1.png"), { 0, 0 }, { 129, 8 }, false };
			m_orange = PTexture{ Texture(texPath4 + L"back_1.png"), { 0, 0 }, { 42, 133 }, false };
			m_green = PTexture{ Texture(texPath4 + L"tail_1.png"), { 0, 0 }, { 112, 153 }, false };
			m_blue = PTexture{ Texture(texPath4 + L"eye_1.png"), { 0, 0 }, { 107, 17 }, false };
			m_purple = PTexture{ Texture(texPath4 + L"ear_1.png"), { 0, 0 }, { 11, 172 }, false };

			m_red = Attach(m_body, m_red, Vec2(28, 199));
			m_orange = Attach(m_body, m_orange, Vec2(139, 35));
			m_green = Attach(m_body, m_green, Vec2(55, 90));
			m_blue = Attach(m_body, m_blue, Vec2(151, 267));
			m_purple = Attach(m_body, m_purple, Vec2(306, 87));

		}

		void draw(const Vec2& basePos, const double baseTheta)const
		{
			if (m_mode == Boss4AnimeMode::Vanished) return;

			Color diffColor = (m_mode != Boss4AnimeMode::Damaged) ? Color(255, 255, 255) : Color(255, 120, 120);

			if (m_mode == Boss4AnimeMode::Damagable)
			{
				switch (m_col)
				{
				case shimi::ShimiColors::Red:
					m_red.draw(basePos, baseTheta, Vec2(0, 0), 0, diffColor);
					break;
				case shimi::ShimiColors::Orange:
					m_orange.draw(basePos, baseTheta, Vec2(0, 0), 0, diffColor);
					break;
				case shimi::ShimiColors::Green:
					m_green.draw(basePos, baseTheta, Vec2(0, 0), 0, diffColor);
					break;
				case shimi::ShimiColors::Blue:
					m_blue.draw(basePos, baseTheta, Vec2(0, 0), 0, diffColor);
					break;
				case shimi::ShimiColors::Purple:
					m_purple.draw(basePos, baseTheta, Vec2(0, 0), 0, diffColor);
					break;
				case shimi::ShimiColors::ColorNum:
					break;
				default:
					break;
				}
			}

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