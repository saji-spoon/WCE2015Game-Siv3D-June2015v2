#pragma once
#include<vector>
#include<Siv3D.hpp>
#include"Enemy.hpp"
#include"Config.hpp"

namespace shimi
{
	class GameBase;

	class EnemyManager
	{
	public:
		EnemyManager(){}

		EnemyManager(GameBase* gb) :m_gb(gb){}

		std::vector<std::shared_ptr<Enemy>> m_enemies;

		struct EnemyData{
			std::shared_ptr<Enemy> m_data;
			bool m_isPop = false;
		};

		std::vector<EnemyData> m_enemyDatabase;

		GameBase* m_gb;

		int registerEnemy(std::shared_ptr<Enemy>& enemyPtr);
		
		void pop();

		void popForce(const Vec2& center, double r);

		void depop();

	private:

	};

}