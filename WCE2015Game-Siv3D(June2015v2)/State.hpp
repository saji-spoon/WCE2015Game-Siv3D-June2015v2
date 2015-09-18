#pragma once
#pragma warning( disable : 4100 )
#include<Siv3D.hpp>

namespace shimi
{

class GameBase;
	
namespace state
{


class GBState
{

public:
	virtual void enter(GameBase* gb) = 0;

	virtual void execute(GameBase* gb) = 0;

	virtual void exit(GameBase* gb) = 0;
};

class MainGame : public GBState
{

public:
	void enter(GameBase* gb){}

	void execute(GameBase* gb);

	void exit(GameBase* gb){}
};

class Menu : public GBState
{
public:
	void enter(GameBase* gb){}

	void execute(GameBase* gb);

	void exit(GameBase* gb){}
};


}}