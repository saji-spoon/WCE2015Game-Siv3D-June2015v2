#pragma once
#pragma warning( disable : 4100 )
#include<Siv3D.hpp>

namespace shimi
{

class GameBase;

class MyVehicle;

class Boss1;
	
namespace state
{

template <typename T>
class StateBase
{
public:
	virtual void enter(T& gb) = 0;

	virtual void execute(T& gb) = 0;

	virtual void exit(T& gb) = 0;
};

class GBState
{

public:
	virtual void draw(const GameBase* gb)const = 0;

	virtual void enter(GameBase* gb) = 0;

	virtual void execute(GameBase* gb) = 0;

	virtual void exit(GameBase* gb) = 0;
};

class MainGame : public GBState
{

public:
	void draw(const GameBase* gb)const override;

	void enter(GameBase* gb)override{}

	void execute(GameBase* gb)override;

	void exit(GameBase* gb)override{}
};

class Menu : public GBState
{
public:
	void draw(const GameBase* gb)const override;

	void enter(GameBase* gb)override;

	void execute(GameBase* gb)override;

	void exit(GameBase* gb)override;
};

namespace myvehicle
{
class MVState
{

public:
	enum StateID
	{
		Normal,
		Damaged
	};

	virtual void enter(MyVehicle& mv) = 0;

	virtual void execute(MyVehicle& mv) = 0;

	virtual void exit(MyVehicle& mv) = 0;

	virtual StateID getStateID()const  = 0;
};

class Normal : public MVState
{
public:
	void enter(MyVehicle& mv)override{}

	void execute(MyVehicle& mv)override;

	void exit(MyVehicle& mv)override{}

	StateID getStateID()const override
	{
		return StateID::Normal;
	}
};

class Damaged : public MVState
{
	//無敵時間を測るタイマー
	int m_damagedTimer = 120;

public:
	void enter(MyVehicle& mv)override;

	void execute(MyVehicle& mv)override;

	void exit(MyVehicle& mv)override;

	StateID getStateID()const override
	{
		return StateID::Damaged;
	}


};

}

namespace boss1
{
using Boss1Base = StateBase<Boss1>;

class Normal : public Boss1Base
{
	int m_timer = 0;

	void enter(Boss1& gb)override;

	void execute(Boss1& gb)override;

	void exit(Boss1& gb)override;
};

class Run : public Boss1Base
{
	void enter(Boss1& gb)override;

	void execute(Boss1& gb)override;

	void exit(Boss1& gb)override;
};

class Stay : public Boss1Base
{
	int m_timer = 0;

	void enter(Boss1& gb)override;

	void execute(Boss1& gb)override;

	void exit(Boss1& gb)override;
};

class Damaged : public Boss1Base
{
	int m_timer = 0;

	void enter(Boss1& gb)override;

	void execute(Boss1& gb)override;

	void exit(Boss1& gb)override;
};

class Vanish : public Boss1Base
{
	int m_timer = 0;

	void enter(Boss1& gb)override;

	void execute(Boss1& gb)override;

	void exit(Boss1& gb)override;
};
}}}