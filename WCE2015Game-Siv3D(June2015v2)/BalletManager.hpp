#pragma once
#include<vector>
#include<Siv3D.hpp>
#include"Ballet.hpp"

namespace shimi
{

class GameBase;

class BalletManager
{
public:
	BalletManager(){}

	BalletManager(GameBase* gb) :m_gb(gb){}

	std::vector<std::shared_ptr<Ballet>> m_ballets;

	GameBase* m_gb;

};

}