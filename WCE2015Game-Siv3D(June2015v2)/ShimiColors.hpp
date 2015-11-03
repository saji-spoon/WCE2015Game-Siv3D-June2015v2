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


	static const std::array<Color, static_cast<size_t>(ShimiColors::ColorNum)+1> ShimiColorsColor =
	{
		Color(224, 0, 0),
		Color(255, 166, 0),
		Color(72, 212, 12),
		Color(55, 122, 238),
		Color(130, 77, 243),
		Color(255, 255, 255),//><
	};

	//à íuìIè„â∫ä÷åW
	static const std::array<ShimiColors, static_cast<size_t>(ShimiColors::ColorNum)> ShimiColorsHierarchy =
	{
		ShimiColors::Green,
		ShimiColors::Red,
		ShimiColors::Orange,
		ShimiColors::Blue,
		ShimiColors::Purple
	};

	String ToSString(const ShimiColors& col);

	ShimiColors ToShimiColors(const String& str);

	//è„â∫èáÇ≈ÇÃèáà ÇéÊìæ
	int ToHierarchy(const ShimiColors& col);

	Color ToColor(const ShimiColors& col);

	ShimiColors NextColor(const ShimiColors& col);

	ShimiColors PreviousColor(const ShimiColors& col);

	std::shared_ptr<Shot> ToShot(ShimiColors col, int level);
}