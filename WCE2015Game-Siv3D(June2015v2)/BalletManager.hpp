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

	BalletManager(GameBase* gb);

	std::vector<Ballet> m_ballets;

	GameBase* m_gb;

};

}