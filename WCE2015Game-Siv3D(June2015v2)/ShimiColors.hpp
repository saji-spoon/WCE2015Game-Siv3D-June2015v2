#pragma once
#include<Siv3D.hpp>


namespace shimi
{
	class Shot;

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

	//ˆÊ’u“Iã‰ºŠÖŒW
	static const std::array<ShimiColors, static_cast<size_t>(ShimiColors::ColorNum)> ShimiColorsHierarchy =
	{
		ShimiColors::Green,
		ShimiColors::Red,
		ShimiColors::Orange,
		ShimiColors::Blue,
		ShimiColors::Purple
	};

	String ToSString(ShimiColors col);

	//ã‰º‡‚Å‚Ì‡ˆÊ‚ğæ“¾
	int ToHierarchy(ShimiColors col);


}