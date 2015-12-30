#pragma once
#pragma warning( disable : 4100 )
#include<Siv3D.hpp>
#include"CameraWork.hpp"
#include"PartAnimation.hpp"


namespace shimi
{

class GameBase;

class MyVehicle;

class Boss1;

class Boss2;
	
class Boss3;

class Boss4;

namespace state
{

template <typename T>
class StateBase
{
public:
	virtual void enter(T& gb) = 0;

	virtual void execute(T& gb) = 0;

	virtual void exit(T& gb) = 0;

	virtual ~StateBase(){}
};

class GBState
{

public:
	virtual void draw(const GameBase* gb)const = 0;

	virtual void enter(GameBase* gb) = 0;

	virtual void execute(GameBase* gb) = 0;

	virtual void exit(GameBase* gb) = 0;

	virtual ~GBState(){}
};

class MainGame : public GBState
{

public:
	void draw(const GameBase* gb)const override;

	void enter(GameBase* gb)override{}

	void execute(GameBase* gb)override;

	void exit(GameBase* gb)override{}

	virtual ~MainGame(){}
};

class Menu : public GBState
{
public:
	void draw(const GameBase* gb)const override;

	void enter(GameBase* gb)override;

	void execute(GameBase* gb)override;

	void exit(GameBase* gb)override;

	virtual ~Menu(){}
};

class Clear : public GBState
{
	int m_timer = 0;

public:
	void draw(const GameBase* gb)const override;

	void enter(GameBase* gb)override;

	void execute(GameBase* gb)override;

	void exit(GameBase* gb)override;

	virtual ~Clear(){}
};

class Event1 : public GBState
{
	CameraWork2 m_camera;

	int m_timer = 0;

public:
	void draw(const GameBase* gb)const override;

	void enter(GameBase* gb)override;

	void execute(GameBase* gb)override;

	void exit(GameBase* gb)override;

	virtual ~Event1(){}
};


namespace myvehicle
{
class MVState
{

public:
	enum StateID
	{
		Normal,
		Damaged,
		Killed,
		Starting,
		ToBoss,

	};

	virtual void enter(MyVehicle& mv) = 0;

	virtual void execute(MyVehicle& mv) = 0;

	virtual void exit(MyVehicle& mv) = 0;

	virtual StateID getStateID()const  = 0;

	virtual ~MVState(){}
};

class Normal : public MVState
{
public:
	void enter(MyVehicle& mv)override;

	void execute(MyVehicle& mv)override;

	void exit(MyVehicle& mv)override;

	StateID getStateID()const override
	{
		return StateID::Normal;
	}

	virtual ~Normal(){}

};

class Damaged : public MVState
{
	//無敵時間を測るタイマー
	int m_damagedTimer = 120;

	FrameExp<double> m_alpha;

public:
	Damaged()
	{
		m_alpha.m_values.push_back({ 2, 0.2 });
		m_alpha.m_values.push_back({ 2, 1.0 });
	}

	void enter(MyVehicle& mv)override;

	void execute(MyVehicle& mv)override;

	void exit(MyVehicle& mv)override;

	StateID getStateID()const override
	{
		return StateID::Damaged;
	}

	virtual ~Damaged(){}

};

class ToBoss : public MVState
{
	int m_timer = 0;

public:
	void enter(MyVehicle& mv)override;

	void execute(MyVehicle& mv)override;

	void exit(MyVehicle& mv)override;

	StateID getStateID()const override
	{
		return StateID::ToBoss;
	}

	virtual ~ToBoss(){}

};

class Killed : public MVState
{
	int m_timer=0;

public:
	void enter(MyVehicle& mv)override;

	void execute(MyVehicle& mv)override;

	void exit(MyVehicle& mv)override;

	StateID getStateID()const override
	{
		return StateID::Killed;
	}

	virtual ~Killed(){}

};

class Starting : public MVState
{
	int m_timer = 0;

public:
	void enter(MyVehicle& mv)override;

	void execute(MyVehicle& mv)override;

	void exit(MyVehicle& mv)override;

	StateID getStateID()const override
	{
		return StateID::Starting;
	}

	virtual ~Starting(){}

};

}

namespace boss1
{
using Boss1Base = StateBase<Boss1>;

class Normal : public Boss1Base
{
public:
	int m_timer = 0;

	void enter(Boss1& gb)override;

	void execute(Boss1& gb)override;

	void exit(Boss1& gb)override;

	virtual ~Normal(){}
};

class Run : public Boss1Base
{
public:

	void enter(Boss1& gb)override;

	void execute(Boss1& gb)override;

	void exit(Boss1& gb)override;

	virtual ~Run(){}

};

class Stay : public Boss1Base
{
public:

	int m_timer = 0;

	void enter(Boss1& gb)override;

	void execute(Boss1& gb)override;

	void exit(Boss1& gb)override;

	virtual ~Stay(){}

};

class Damaged : public Boss1Base
{
public:

	int m_timer = 0;

	void enter(Boss1& gb)override;

	void execute(Boss1& gb)override;

	void exit(Boss1& gb)override;

	virtual ~Damaged(){}

};

class Vanish : public Boss1Base
{
public:

	int m_timer = 0;

	void enter(Boss1& gb)override;

	void execute(Boss1& gb)override;

	void exit(Boss1& gb)override;

	virtual ~Vanish(){}

};
}

namespace boss2
{
using Boss2Base = StateBase<Boss2>;

class Normal : public Boss2Base
{
	int m_timer = 0;

public:
	void enter(Boss2& gb)override;

	void execute(Boss2& gb)override;

	void exit(Boss2& gb)override;

	virtual ~Normal(){}
};

class Barrier : public Boss2Base
{
public:
	void enter(Boss2& gb)override;

	void execute(Boss2& gb)override;

	void exit(Boss2& gb)override;

	virtual ~Barrier(){}
};

class Stay : public Boss2Base
{
public:

	int m_timer = 0;

	void enter(Boss2& gb)override;

	void execute(Boss2& gb)override;

	void exit(Boss2& gb)override;

	virtual ~Stay(){}

};

class Damagable : public Boss2Base
{
	int m_timer = 0;

public:
	void enter(Boss2& gb)override;

	void execute(Boss2& gb)override;

	void exit(Boss2& gb)override;

	virtual ~Damagable(){}
};

class Damaged : public Boss2Base
{
public:

	int m_timer = 0;

	void enter(Boss2& gb)override;

	void execute(Boss2& gb)override;

	void exit(Boss2& gb)override;

	virtual ~Damaged(){}

};

class Vanish : public Boss2Base
{
public:

	int m_timer = 0;

	void enter(Boss2& gb)override;

	void execute(Boss2& gb)override;

	void exit(Boss2& gb)override;

	virtual ~Vanish(){}

};



}

namespace boss3
{
	using Boss3Base = StateBase<Boss3>;

	class Normal : public Boss3Base
	{
		int m_timer = 0;

	public:
		void enter(Boss3& gb)override;

		void execute(Boss3& gb)override;

		void exit(Boss3& gb)override;

		virtual ~Normal(){}
	};

	class Barrier : public Boss3Base
	{
	public:
		void enter(Boss3& gb)override;

		void execute(Boss3& gb)override;

		void exit(Boss3& gb)override;

		virtual ~Barrier(){}
	};

	class Damagable : public Boss3Base
	{
		int m_timer = 0;
	public:
		void enter(Boss3& gb)override;

		void execute(Boss3& gb)override;

		void exit(Boss3& gb)override;

		virtual ~Damagable(){}
	};

	class Damaged : public Boss3Base
	{
		int m_timer = 0;
	public:
		void enter(Boss3& gb)override;

		void execute(Boss3& gb)override;

		void exit(Boss3& gb)override;

		virtual ~Damaged(){}
	};

	class Vanish : public Boss3Base
	{
		int m_timer = 0;
	public:
		void enter(Boss3& gb)override;

		void execute(Boss3& gb)override;

		void exit(Boss3& gb)override;

		virtual ~Vanish(){}
	};

	class Stay : public Boss3Base
	{
	public:

		int m_timer = 0;

		void enter(Boss3& gb)override;

		void execute(Boss3& gb)override;

		void exit(Boss3& gb)override;

		virtual ~Stay(){}

	};


}

namespace boss4
{
	using Boss4Base = StateBase<Boss4>;

	class Normal : public Boss4Base
	{
		int m_timer = 0;

	public:
		void enter(Boss4& gb)override;

		void execute(Boss4& gb)override;

		void exit(Boss4& gb)override;

		virtual ~Normal(){}
	};

	class Attack : public Boss4Base
	{
	public:
		void enter(Boss4& gb)override;

		void execute(Boss4& gb)override;

		void exit(Boss4& gb)override;

		virtual ~Attack(){}
	};

	class Damagable : public Boss4Base
	{
		int m_timer = 0;
	public:
		void enter(Boss4& gb)override;

		void execute(Boss4& gb)override;

		void exit(Boss4& gb)override;

		virtual ~Damagable(){}
	};

	class Damaged : public Boss4Base
	{
		int m_timer = 0;
	public:
		void enter(Boss4& gb)override;

		void execute(Boss4& gb)override;

		void exit(Boss4& gb)override;

		virtual ~Damaged(){}
	};

	class Vanished : public Boss4Base
	{
		int m_timer = 0;
	public:
		void enter(Boss4& gb)override;

		void execute(Boss4& gb)override;

		void exit(Boss4& gb)override;

		virtual ~Vanished(){}
	};

	class Stay : public Boss4Base
	{
	public:

		int m_timer = 0;

		void enter(Boss4& gb)override;

		void execute(Boss4& gb)override;

		void exit(Boss4& gb)override;

		virtual ~Stay(){}

	};


}
}
};