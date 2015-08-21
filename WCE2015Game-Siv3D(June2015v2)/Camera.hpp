#pragma once
#include<Siv3D.hpp>

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

	//�S�̃}�b�v�̍��W����A�J�����Z���^�[�̂Ƃ��A��ʏ�łǂ��Ɉʒu���邩�̍��W��Ԃ�
	inline Vec2 getDrawPos(const Vec2& globalPos)const
	{
		return Vec2{ 640.0, 400.0 } +globalPos - m_pos;
	}

	Vec2 m_pos;

private:

	D2Camera()
	{
	}
};

}