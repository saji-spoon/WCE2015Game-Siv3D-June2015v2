#pragma once
#include<Siv3D.hpp>
#include"ShimiColors.hpp"
#include"MyVehicle.hpp"

namespace shimi
{

	struct MyVehicleSave
	{
		struct ShotBox
		{
			Optional<ShimiColors> m_color;
		};

		Vec2 m_mvPos;
		std::array<MyVehicle::ShotManager::ShotProperty, static_cast<size_t>(ShimiColors::ColorNum)> m_shotPropertys;
		int m_equipNum;
		std::vector<Optional<ShotBox>> m_equipShot;

	};


	template <class Char> // 出力ストリーム
	inline std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const MyVehicleSave& cl)
	{
		return os << L'(' << cl.m_mvPos << L',' << cl.m_equipNum << L',' << cl.m_shotPropertys << L',' << cl.m_equipShot << L')';
	}


	template <class Char> // 入力ストリーム
	inline std::basic_istream<Char>& operator >>(std::basic_istream<Char>& is, MyVehicleSave& cl)
	{
		Char unused;

		//LogStream(is);
		is >> unused >> cl.m_mvPos;
		is >> unused >> cl.m_equipNum;
		is >> unused >> cl.m_shotPropertys;
		//LogStream(is);
		is	>> unused >> cl.m_equipShot >> unused;
		//LogStream(is);

		return is;
	}


	template <class Char> // 出力ストリーム
	inline std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const MyVehicleSave::ShotBox& cl)
	{
		return os << L'(' << cl.m_color << L')';
	}


	template <class Char> // 入力ストリーム
	inline std::basic_istream<Char>& operator >>(std::basic_istream<Char>& is, MyVehicleSave::ShotBox& cl)
	{
		Char unused;

		return is >> unused >> cl.m_color >> unused;
	}

}
