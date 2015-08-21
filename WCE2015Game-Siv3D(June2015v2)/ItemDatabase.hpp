#pragma once
#include<Siv3D.hpp>
#include"ShimiColors.hpp"

namespace shimi
{

struct ItemRecord
{
	bool m_get = false;

	int m_value;

	ShimiColors m_color;

	ItemRecord(ShimiColors col, int value) :m_value(value), m_color(col)
	{
	}

	String toString()const
	{
		return L"Color:" + ToSString(m_color) + L", Value:" + Format(m_value) + L", " + Format(m_get);
	}
};

class ItemDetabase
{
public:

	std::vector<ItemRecord> m_list;

	ItemDetabase(){}

	int Register(const ItemRecord& ir)
	{
		const int id = m_list.size();

		m_list.push_back(ir);

		return id;
	}

	void got(int id)
	{
		m_list[id].m_get = true;
	}

	bool isgot(int id)const
	{
		return m_list[id].m_get;
	}

	void debug()const
	{
		String str;

		for (auto& rec : m_list)
		{
			str += rec.toString() + L"\n";
		}

		FontAsset(L"Debug").draw(str, {(0,0), (0,0)}, Palette::Black);
	}
};

}
