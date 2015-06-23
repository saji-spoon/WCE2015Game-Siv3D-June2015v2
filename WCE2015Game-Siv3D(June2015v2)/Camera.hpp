#include<Siv3D.hpp>
#include<HamFramework.hpp>

class D2Camera {

public:

	D2Camera(){}

	D2Camera(const Vec2& v) :m_pos(v)
	{}

	//�S�̃}�b�v�̍��W����A�J�����Z���^�[�̂Ƃ��A��ʏ�łǂ��Ɉʒu���邩�̍��W��Ԃ�
	inline Vec2 getDrawPos(const Vec2& globalPos)const 
	{
		return Vec2{ 640.0, 400.0 } + globalPos - m_pos;
	}

	Vec2 m_pos;
};
