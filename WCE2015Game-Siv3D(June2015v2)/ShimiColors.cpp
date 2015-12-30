#include"ShimiColors.hpp"
#include"Shot.hpp"

using namespace shimi;


String shimi::ToSString(const ShimiColors& col)
{
	const size_t index = static_cast<size_t>(col);

	return ShimiColorsStr[index];
}

ShimiColors shimi::ToShimiColors(const String& str)
{
	
	const auto& it = std::find(ShimiColorsStr.begin(), ShimiColorsStr.end(), str);

	if (it == ShimiColorsStr.end())
	{
		LOG_ERROR(L"No Such ShimiColorStr:", str);
		return ShimiColors::Red;
	}
	
	size_t index = std::distance(ShimiColorsStr.begin(), it);

	return static_cast<ShimiColors>(index);

}


int shimi::ToHierarchy(const ShimiColors& col)
{
	for (size_t i = 0; i < ShimiColorsHierarchy.size(); ++i)
	{
		if (ShimiColorsHierarchy[i] == col)
		{
			return i;
		}
	}

	assert(false);

	return 0;
}

Color shimi::ToColor(const ShimiColors& col)
{
	const size_t index = static_cast<size_t>(col);

	return ShimiColorsColor[index];
}

ShimiColors shimi::NextColor(const ShimiColors& col)
{
	return static_cast<ShimiColors>((static_cast<int>(col)+1) % static_cast<int>(ShimiColors::ColorNum));
}

ShimiColors shimi::PreviousColor(const ShimiColors& col)
{
	return static_cast<ShimiColors>((static_cast<int>(col)+static_cast<int>(ShimiColors::ColorNum)-1) % static_cast<int>(ShimiColors::ColorNum));
}
