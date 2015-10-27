#pragma once
#include<Siv3D.hpp>
#include"Config.hpp"

namespace shimi
{

class D2Camera 
{
public:

	static D2Camera* I()
	{
		static D2Camera instance;
		return &instance;
	}

	D2Camera(const D2Camera& rhs) = delete;

	D2Camera& operator=(const D2Camera& rhs) = delete;

	//全体マップの座標から、カメラセンターのとき、画面上でどこに位置するかの座標を返す
	inline Vec2 getDrawPos(const Vec2& globalPos)const
	{
		return ConfigParam::CAMERA_POSITION + globalPos - m_pos;
	}

	//画面内での位置から、全体マップの座標を返す。
	inline Vec2 getGlobalPos(const Vec2& drawPos)const
	{
		return m_pos - ConfigParam::CAMERA_POSITION + drawPos;
	}

	Vec2 m_pos;

private:

	D2Camera()
	{
	}
};

}