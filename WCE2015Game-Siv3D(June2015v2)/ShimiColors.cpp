#include"ShimiColors.hpp"

String shimi::ToSString(ShimiColors col)
{
	const size_t index = static_cast<size_t>(col);

	return ShimiColorsStr[index];
}