#pragma once
#include<Siv3D.hpp>

namespace shimi
{
	enum class ShimiColors
	{
		Red,
		Orange,
		Green,
		Blue,
		Purple,
		ColorNum
	};

	static const std::array<String, static_cast<size_t>(ShimiColors::ColorNum)+1> ShimiColorsStr =
	{
		L"Red",
		L"Orange",
		L"Green",
		L"Blue",
		L"Purple",
		L"ColorNum:Not ShimiColor"
	};

	String ToSString(ShimiColors col);
}