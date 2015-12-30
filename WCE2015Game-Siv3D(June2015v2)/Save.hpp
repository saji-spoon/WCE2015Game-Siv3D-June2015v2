#pragma once
#include<Siv3D.hpp>
#include"ItemObject.hpp"
#include"ContainerStream.hpp"
#include"MyVehicle.hpp"
#include"MyVehicleSave.hpp"

namespace shimi
{

class GameBase;

struct SaveStruct
{
	//自機のデータを保存
	MyVehicleSave m_mvs;
	//前回復活位置をセーブ

	//残ってるアイテムがあれば保存
	std::vector<ItemObject> m_items;
	std::array<bool, 4> m_bossBeated;
	bool m_isDoorOpen = false;
	std::vector<String> m_brokenObstacles;
	Vec2 m_recoverPos;
};

template <class Char>
inline
std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const SaveStruct& cl)
{
	os
		<< cl.m_items << '\n'
		<< cl.m_bossBeated << '\n'
		<< cl.m_brokenObstacles << '\n';
	os << cl.m_mvs << '\n';
	os << cl.m_isDoorOpen << '\n';
	os << cl.m_recoverPos;
	return os;
}

template <class Char>
inline
std::basic_istream<Char>& operator >>(std::basic_istream<Char>& is, SaveStruct& cl)
{
	is
		>> cl.m_items
		>> cl.m_bossBeated;

	//LogStream(is);

	is	>> cl.m_brokenObstacles;

	//LogStream(is);

	is >> cl.m_mvs;

	is >> cl.m_isDoorOpen;

	is >> cl.m_recoverPos;

	//LogStream(is);

	return is;

}

class Save{
public:

	static Save* I()
	{
		static Save instance;
		return &instance;
	}

	Save(const Save& rhs) = delete;

	Save& operator=(const Save& rhs) = delete;

	bool load(GameBase& gb, const FilePath& path = L"Save/save1");

	bool save(const GameBase& gb, const FilePath& path = L"Save/save1");

	SaveStruct m_save;

private:

	bool getData(const GameBase& gb);

	bool loadSaveData(const FilePath& path = L"Save/save1");

	Save()
	{
	}
};
}
