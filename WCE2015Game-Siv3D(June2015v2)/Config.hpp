#pragma once
#include<Siv3D.hpp>
#include"GamePadCheck.hpp"

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

	const static Size SIZE_OF_NORMALWORLD;
	const static Size SIZE_OF_WORLDMARGIN;
	const static Size SIZE_OF_BOSSWORLD;
	const static Size SIZE_OF_WORLD;
	//ワールドを囲む壁の縦と横


	const static bool KEY_UP_CLICKED();
	const static bool KEY_RIGHT_CLICKED();
	const static bool KEY_LEFT_CLICKED();
	const static bool KEY_DOWN_CLICKED();
	const static bool KEY_RIGHT_PRESSED();
	const static bool KEY_LEFT_PRESSED();
	const static bool KEY_A_CLICKED();
	const static bool KEY_A_PRESSED();
	const static bool KEY_B_CLICKED();
	const static bool KEY_B_PRESSED();

};


}