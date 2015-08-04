#pragma once
#include<Siv3D.hpp>
#include"Camera.hpp"

namespace shimi
{
class Obstacle
{
public:

	Obstacle(){}

	Obstacle(const Point& pos, const FilePath& imagePath, double simp = 3.0) : m_pols(Imaging::FindExternalContours(Image(imagePath), true).simplified(simp) + pos), m_tex(imagePath), m_pos(pos)
	{
#ifdef _DEBUG
		LOG_DEBUG(L"Obstacle Constracted:", Format(m_pols));
#endif
	}

	MultiPolygon m_pols;

	Texture m_tex;

	Point m_pos;

	void draw(const D2Camera camera)const
	{
		m_tex.draw(camera.getDrawPos(m_pos));
	}

	void drawDebug(const D2Camera camera)const
	{
		const Vec2 drawPos = camera.getDrawPos(m_pos);

		m_pols.drawFrame(drawPos, 2, Color(40, 200, 200, 30));

		for (const auto& p : m_pols)
		{
			const auto& outer = p.outer();

			for (const auto& o : outer)
			{
				Circle(drawPos + o, 5).draw(Color(255, 0, 0, 40));
			}
		}
	}
};

}