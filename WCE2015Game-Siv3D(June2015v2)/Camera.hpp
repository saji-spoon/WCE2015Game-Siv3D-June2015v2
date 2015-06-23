#include<Siv3D.hpp>
#include<HamFramework.hpp>

class D2Camera {

public:

	D2Camera(){}

	D2Camera(const Vec2& v) :m_pos(v)
	{}

	//全体マップの座標から、カメラセンターのとき、画面上でどこに位置するかの座標を返す
	inline Vec2 getDrawPos(const Vec2& globalPos)const 
	{
		return Vec2{ 640.0, 400.0 } + globalPos - m_pos;
	}

	Vec2 m_pos;
};
