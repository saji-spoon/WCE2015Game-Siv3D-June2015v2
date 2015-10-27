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
	//画面左上を原点としたときの、カメラのm_posの位置
	const static Vec2 CAMERA_POSITION;

	const static int TIME_GREENCHARGE;
	const static int TIME_GREENBURST;
	const static int R_OF_MYVEHICLE;
};

}