#pragma once
#include<Siv3D.hpp>
#include"Camera.hpp"

namespace shimi
{

struct DebugPoint
{
	std::vector<Point> m_list;

	void draw()const
	{
		for (const auto& p : m_list)
		{
			const Vec2 DrawPos = D2Camera::I()->getDrawPos(p);

			Circle(DrawPos, 5).draw(Palette::Red);
			FontAsset(L"Debug").draw(Format(p), DrawPos + Vec2(5, 5), Palette::Black);
		}
	}

	void update()
	{
		if (Mouse::RightClicked())
		{
			m_list.push_back(D2Camera::I()->getGlobalPos(Mouse::Pos()).asPoint());
		}
	}
};
}