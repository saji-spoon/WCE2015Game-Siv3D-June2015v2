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
		Color(223, 52, 52),
		Color(255, 166, 0),
		Color(118, 224, 72),
		Color(55, 122, 238),
		Color(130, 77, 243),
		Color(255, 255, 255),//><
	};

	//位置的上下関係
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

	//上下順での順位を取得
	int ToHierarchy(const ShimiColors& col);

	Color ToColor(const ShimiColors& col);

	ShimiColors NextColor(const ShimiColors& col);

	ShimiColors PreviousColor(const ShimiColors& col);

	std::shared_ptr<Shot> ToShot(ShimiColors col, int level);

	template <class Char> // 出力ストリーム
	inline std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const ShimiColors& col)
	{
		return os << Char('(') << static_cast<int>(col) << Char(')');
	}

	template <class Char> // 入力ストリーム
	inline std::basic_istream<Char>& operator >>(std::basic_istream<Char>& is, ShimiColors& col)
	{
		Char unused;

		int c;

		is >> unused >> c >> unused;

		col = static_cast<ShimiColors>(c);

		return is;

	}
}