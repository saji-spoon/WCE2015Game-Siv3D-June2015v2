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

		void registerEnemy(std::shared_ptr<Enemy>&& enemyPtr);

		void pop();

		void popForce(const Vec2& center, double r);

		void depop();

	private:

	};

}