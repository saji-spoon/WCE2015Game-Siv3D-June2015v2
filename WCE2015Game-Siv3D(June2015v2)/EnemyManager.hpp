#pragma once
#include<vector>
#include<Siv3D.hpp>
#include"Enemy.hpp"

namespace shimi
{
	class GameBase;

	class EnemyManager
	{
	public:
		EnemyManager(){}

		EnemyManager(GameBase* gb) :m_gb(gb){}

		std::vector<std::shared_ptr<Enemy>> m_enemies;

		GameBase* m_gb;

	};

}