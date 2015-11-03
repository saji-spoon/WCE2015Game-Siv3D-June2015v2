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
			EnemyData(const std::shared_ptr<Enemy>& data) :m_data(data)
			{
			}

			std::shared_ptr<Enemy> m_data;
			bool m_isPop = false;
		};

		std::vector<EnemyData> m_enemyDatabase;

		GameBase* m_gb;

		int registerEnemy(std::shared_ptr<Enemy>& enemyPtr, const Optional<ItemRecord>& item);
		
		void pop();

		void popForce(const Vec2& center, double r);

		void depop();

	private:

	};

}