#pragma once
#include<Siv3D.hpp>

namespace shimi
{
	void SaveMultiPolygon(const FilePath& path, const MultiPolygon& mp);
	
	MultiPolygon LoadMultiPolygon(const FilePath& path);
};
