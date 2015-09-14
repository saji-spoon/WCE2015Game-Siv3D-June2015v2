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

		std::vector<CoEnemy> m_enemies;

		struct EnemyData{
			EnemyData(CoEnemy&& enemy) :m_data(std::move(enemy)){}
			EnemyData(const EnemyData& enemy) = default;
			EnemyData(EnemyData&& enemy)  _NOEXCEPT
			: m_data(std::move(enemy.m_data))
			{}
			~EnemyData() = default;

			CoEnemy m_data;
			bool m_isPop = false;
		};

		std::vector<EnemyData> m_enemyDatabase;

		GameBase* m_gb;

		void registerEnemy(std::shared_ptr<Enemy>&& enemyPtr)
		{
			m_enemyDatabase.emplace_back(std::move(CoEnemy{static_cast<int>(m_enemyDatabase.size()), std::move(enemyPtr)}));
		}

		void pop();

		void popForce(const Vec2& center, double r);

		void depop()
		{
			Erase_if(m_enemies, [&](const CoEnemy& e){
				const bool f = e.m_enemy->isDead();

				if (f)
				{
					const int id = e.m_id;

					m_enemyDatabase[id].m_isPop = false;
				}

				return f; 
			});
		}

	private:

	};

}