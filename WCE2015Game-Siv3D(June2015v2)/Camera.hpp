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

	//�S�̃}�b�v�̍��W����A�J�����Z���^�[�̂Ƃ��A��ʏ�łǂ��Ɉʒu���邩�̍��W��Ԃ�
	inline Vec2 getDrawPos(const Vec2& globalPos)const
	{
		return ConfigParam::CAMERA_POSITION + globalPos - m_pos;
	}

	//��ʓ��ł̈ʒu����A�S�̃}�b�v�̍��W��Ԃ��B
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