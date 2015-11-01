#include"Config.hpp"
#include"Shot.hpp"

using namespace shimi;

const double ConfigParam::POP_DISTANCE_IN = 760.0;
const double ConfigParam::POP_DISTANCE_OUT = 850.0;
const double ConfigParam::DEPOP_DISTANCE = 900.0;
const int ConfigParam::DEPOP_COUNT = 60;
const Vec2 ConfigParam::CAMERA_POSITION = Vec2(640, 400);

const int ConfigParam::TIME_GREENCHARGE = 60;
const int ConfigParam::TIME_GREENBURST = 5;

const int ConfigParam::R_OF_MYVEHICLE = 20;

const Size ConfigParam::SIZE_OF_WORLD = Size(8500, 7300);

const bool ConfigParam::KEY_UP_CLICKED()
{
	return Input::KeyUp.clicked || GamepadCheck::I()->upClicked();
}

const bool ConfigParam::KEY_RIGHT_CLICKED()
{
	return Input::KeyRight.clicked || GamepadCheck::I()->rightClicked();
}

const bool ConfigParam::KEY_LEFT_CLICKED()
{
	return Input::KeyLeft.clicked || GamepadCheck::I()->leftClicked();
}

const bool ConfigParam:: KEY_RIGHT_PRESSED()
{
	return Input::KeyRight.pressed || Gamepad(0).x == 1;
}

const bool ConfigParam:: KEY_LEFT_PRESSED()
{
	return Input::KeyLeft.pressed || Gamepad(0).x == -1;
}

const bool ConfigParam:: KEY_DOWN_CLICKED()
{
	return Input::KeyDown.clicked || GamepadCheck::I()->downClicked();
}

const bool ConfigParam:: KEY_A_CLICKED()
{
	return Input::KeyZ.clicked ||  Gamepad(0).button(3).clicked;
}

const bool ConfigParam:: KEY_A_PRESSED()
{
	return Input::KeyZ.pressed || Gamepad(0).button(3).pressed;
}

const bool ConfigParam:: KEY_B_CLICKED()
{
	return Input::KeyX.clicked || Gamepad(0).button(2).clicked;
}

const bool ConfigParam:: KEY_B_PRESSED()
{
	return Input::KeyX.pressed || Gamepad(0).button(2).pressed;
}







