#pragma once
#include<Siv3D.hpp>
#include"Camera.hpp"
#include"ShimiColors.hpp"

namespace shimi
{

class ItemObject
{
	template <class Char> // 出力ストリーム
	friend
		std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const ItemObject& cl);

	template <class Char> // 入力ストリーム
	friend
		std::basic_istream<Char>& operator >>(std::basic_istream<Char>& is, ItemObject& cl);

	private:
		Vec2 m_pos;

	public:

		bool m_isDead = false;

		ItemObject(){}
		ItemObject::ItemObject(const Vec2& pos)
			:m_pos(pos)
		{}

		void draw()const
		{
			Circle(D2Camera::I()->getDrawPos(m_pos), 20).draw(Palette::White);
			Circle(D2Camera::I()->getDrawPos(m_pos), 20).drawFrame(0.0, 5.0, Color(200,200,200));
		}

		inline Circle getCollision()
		{
			return Circle(m_pos, 20);
		}
		
};

template <class Char> // 出力ストリーム
inline 
std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const ItemObject& cl)
{
	return os << L'(' << cl.m_isDead << L',' << cl.m_pos << L')';
}

template <class Char> // 入力ストリーム
inline
std::basic_istream<Char>& operator >>(std::basic_istream<Char>& is, ItemObject& cl)
{
	Char unused;
	return is >> unused >> cl.m_isDead >> unused >> cl.m_pos >> unused;
}

}