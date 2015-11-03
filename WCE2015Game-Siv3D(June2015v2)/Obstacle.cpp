#include"Obstacle.hpp"

using namespace shimi;

Obstacle::Obstacle(const Point& pos, const FilePath& imagePath, double simp = 3.0) : ObstacleBase(pos, MultiPolygon()), m_tex(imagePath)
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
		TextReader reader(polDataTXT);

		m_pols = Parse<MultiPolygon>(reader.readContents());
	}
	else
	{
		m_pols = MultiPolygon(Imaging::FindExternalContours(Image(imagePath), true).simplified(simp) + pos);

		TextWriter writer(polDataTXT);

		writer.write(Format(m_pols));
	}
	/*
	const auto& outer = m_pols.outer

	for (auto& pols : m_pols)
	{

	}
	*/


#ifdef _DEBUG
	//LOG_DEBUG(L"Obstacle Constracted:", Format(m_pols));
#endif
}

void ObstacleBase::drawDebug()const
{
	const Vec2 drawPos = D2Camera::I()->getDrawPos(m_pos);

	m_pols.draw(D2Camera::I()->getDrawPos(Vec2(0,0)), Color(40, 200, 200, 30));

	//m_pols.boundingRect.movedBy(drawPos).draw(Alpha(128)*Palette::Red);

	for (const auto& p : m_pols)
	{
		p.boundingRect.movedBy(drawPos).draw(Alpha(60)*Palette::Gray);
	}

	for (const auto& p : m_pols)
	{
		const auto& outer = p.outer();
		/*	//ëSÇƒÇÃï«ÇÃLineÇ…Ç¬Ç¢ÇƒÅAwallLinesÇ÷
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

BreakableObstacle::BreakableObstacle(const Rect& rect, const ShimiColors& col)
	:ObstacleBase(rect.pos, MultiPolygon({rect.asPolygon()})),
	m_rect(rect),
	m_col(col)
{
}

void BreakableObstacle::draw()const
{
	m_rect.movedBy(D2Camera::I()->getDrawPos({ 0, 0 }).asPoint()).draw(ToColor(m_col).setAlpha(128));
	m_rect.movedBy(D2Camera::I()->getDrawPos({ 0, 0 }).asPoint()).drawFrame(4.0, 0.0, ToColor(m_col));
}

bool BreakableObstacle::shotByColor(const Optional<ShimiColors>& col)
{
	if (!col) return false;

	return col.value() == m_col;
}

TriggerBreakableObject::TriggerBreakableObject(const Rect& rect, const String& tag)
	:ObstacleBase(rect.pos, MultiPolygon({ rect.asPolygon() }), tag),
	m_rect(rect)
{

}

void TriggerBreakableObject::draw()const
{
	m_rect.movedBy(D2Camera::I()->getDrawPos({ 0, 0 }).asPoint()).draw(Color(120, 120, 120).setAlpha(128));
	m_rect.movedBy(D2Camera::I()->getDrawPos({ 0, 0 }).asPoint()).drawFrame(4.0, 0.0, Color(120, 120, 120));
}


