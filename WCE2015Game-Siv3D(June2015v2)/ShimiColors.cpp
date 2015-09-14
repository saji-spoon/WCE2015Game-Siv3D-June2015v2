#include"ShimiColors.hpp"
#include"Shot.hpp"

String shimi::ToSString(ShimiColors col)
{
	const size_t index = static_cast<size_t>(col);

	return ShimiColorsStr[index];
}

int shimi::ToHierarchy(ShimiColors col)
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
