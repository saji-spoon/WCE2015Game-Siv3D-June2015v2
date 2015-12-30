#include"SaveLoadMultiPolygon.hpp"

void shimi::SaveMultiPolygon(const FilePath& path, const MultiPolygon& mp)
{
	Array<Polygon> polygons;
	
		for (auto i : step(mp.num_polygons))
		{
			if (!mp.polygon(i).isEmpty)
			{
				polygons.push_back(mp.polygon(i));
			}
		}
	
		TextWriter(path).write(MultiPolygon(std::move(polygons)));
}

MultiPolygon shimi::LoadMultiPolygon(const FilePath& path)
{
	String line;
	TextReader(path).readLine(line);
	return MultiPolygon(line);
}
