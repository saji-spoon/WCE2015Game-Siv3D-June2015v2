#include"Obstacle.hpp"

using namespace shimi;

Obstacle::Obstacle(const Point& pos, const FilePath& imagePath, double simp = 3.0) : m_tex(imagePath), m_pos(pos)
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


#ifdef _DEBUG
	//LOG_DEBUG(L"Obstacle Constracted:", Format(m_pols));
#endif
}

void Obstacle::drawDebug()const
{
	const Vec2 drawPos = D2Camera::I()->getDrawPos(m_pos);

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
