#pragma once
#include<Siv3D.hpp>

namespace shimi
{

struct ConfigParam
{
	const static double POP_DISTANCE_IN;
	const static double POP_DISTANCE_OUT;
	const static double DEPOP_DISTANCE;	
	const static int DEPOP_COUNT;
	//��ʍ�������_�Ƃ����Ƃ��́A�J������m_pos�̈ʒu
	const static Vec2 CAMERA_POSITION;

	const static int TIME_GREENCHARGE;
	const static int TIME_GREENBURST;
	const static int R_OF_MYVEHICLE;
};

}