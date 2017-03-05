#include"Obstacle.hpp"
#include"SaveLoadMultiPolygon.hpp"

using namespace shimi;

Obstacle::Obstacle(const s3d::Point& pos, const FilePath& imagePath, double simp = 3.0) : ObstacleBase(pos, MultiPolygon()), m_tex(imagePath)
{
	if (!FileSystem::Exists(imagePath))
	{
		LOG_ERROR(L"Obstacle:Failed to Open File:" + imagePath);
		return;
	}

	const String dir = FileSystem::ParentPath(imagePath);
	const String name = FileSystem::BaseName(imagePath);
	const String polDataTXT = dir + name + L".pol";

	if (FileSystem::Exists(polDataTXT))
	{
		m_pols = LoadMultiPolygon(polDataTXT);
	}
	else
	{
		m_pols = MultiPolygon(Imaging::FindExternalContours(Image(imagePath), true).simplified(simp) + pos);

		SaveMultiPolygon(polDataTXT, m_pols);
	}

#ifdef _DEBUG
	//LOG_DEBUG(L"Obstacle Constracted:", Format(m_pols));
#endif
}

void ObstacleBase::drawDebug()const
{
	const Vec2 drawPos = D2Camera::I()->getDrawPos(Vec2(0,0));

	m_pols.draw(D2Camera::I()->getDrawPos(Vec2(0,0)), Color(40, 200, 200, 30));

	m_pols.boundingRect.movedBy(drawPos).draw(Alpha(128)*Palette::Red);

	for (const auto& p : m_pols)
	{
		p.boundingRect.movedBy(drawPos).draw(Alpha(60)*Palette::Gray);
	}



	for (const auto& p : m_pols)
	{
		const auto& outer = p.outer();
		/*	//全ての壁のLineについて、wallLinesへ
		for (size_t i = 0; i < outer.size(); ++i)
		{
			const Line line(outer[i], outer[(i + 1) % outer.size()]);

			line.movedBy(drawPos).drawArrow(2, Vec2(6.0, 10.0), Palette::Greenyellow);
		}*/

		for (const auto& o : outer)
		{
			Circle(drawPos + o, 5).draw(Color(255, 0, 0, 40));
		}
	}
}

TexturedObstacle::TexturedObstacle(const Point& pos, const FilePath& imagePath, double simp, const Optional<String>& tag)
	:ObstacleBase(pos, MultiPolygon(), tag)
{
	setTextureAndPolygon(imagePath, simp);
}

TexturedObstacle::TexturedObstacle(const Point& pos, const Optional<String>& tag)
	: ObstacleBase(pos, MultiPolygon(), tag)
{
}

void TexturedObstacle::draw()const
{
	m_tex.draw(D2Camera::I()->getDrawPos(m_pos));
}

void TexturedObstacle::setTextureAndPolygon(const FilePath& imagePath, double simp)
{
	if (!FileSystem::Exists(imagePath))
	{
		LOG_ERROR(L"Obstacle:Failed to Open File:" + imagePath);
		return;
	}

	m_tex = Texture(imagePath);

	const String dir = FileSystem::ParentPath(imagePath);
	const String name = FileSystem::BaseName(imagePath);
	const String polDataTXT = dir + name + L".pol";

	if (FileSystem::Exists(polDataTXT))
	{
		TextReader reader(polDataTXT);

		m_pols = Parse<MultiPolygon>(reader.readContents()) + m_pos;
	}
	else
	{
		const MultiPolygon tempPol = MultiPolygon(Imaging::FindExternalContours(Image(imagePath), true).simplified(simp));

		TextWriter writer(polDataTXT);

		writer.write(Format(tempPol));

		m_pols = tempPol + m_pos;
	}
}

BreakableObstacle::BreakableObstacle(const Rect& rect, const ShimiColors& col)
	:TexturedObstacle(rect.pos),
	m_rect(rect),
	m_col(col),
	m_type(Type::Rect)
{
	m_pols = MultiPolygon({ rect.asPolygon() });
}

BreakableObstacle::BreakableObstacle(const Point& pos, const FilePath& imagePath, const ShimiColors& col, double simp)
	:
	TexturedObstacle(pos, imagePath),
	m_col(col),
	m_type(Type::Texture)
{
}

void BreakableObstacle::draw()const
{
	switch (m_type)
	{
	case shimi::BreakableObstacle::Type::Rect:
		m_rect.movedBy(D2Camera::I()->getDrawPos({ 0, 0 }).asPoint()).draw(ToColor(m_col).setAlpha(128));
		m_rect.movedBy(D2Camera::I()->getDrawPos({ 0, 0 }).asPoint()).drawFrame(4.0, 0.0, ToColor(m_col));
		break;
	case shimi::BreakableObstacle::Type::Texture:
		TexturedObstacle::draw();
		break;
	default:
		break;
	}

}

bool BreakableObstacle::shotByColor(const Optional<ShimiColors>& col)
{
	if (!col) return false;

	return col.value() == m_col;
}

TriggerBreakableObject::TriggerBreakableObject(const Point& pos, const FilePath& imagePath, const String& tag, double simp)
	:TexturedObstacle(pos, imagePath, simp, tag)
{
}

void RectObstacle::draw()const
{
	const Point DrawPosBase = D2Camera::I()->getDrawPos(Vec2(0,0)).asPoint();

	switch (m_type)
	{
	case shimi::RectObstacle::Type::White:
		//m_rect.movedBy(DrawPosBase).draw(Palette::White);
		m_rect.movedBy(DrawPosBase).drawFrame(12.0, 0.0, Color(176, 176, 176));
		break;
	case shimi::RectObstacle::Type::Black:
		m_rect.movedBy(DrawPosBase).draw(Color(65, 65, 65));
		m_rect.movedBy(DrawPosBase).drawFrame(12.0, 0.0, Color(43, 43, 43));
		break;
	default:
		break;
	}


}

