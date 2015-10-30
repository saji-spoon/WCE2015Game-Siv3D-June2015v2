#pragma once
#pragma warning (disable : 4239)

#include<Siv3D.hpp>
#include"BalletManager.hpp"
#include"EnemyManager.hpp"
#include"MyVehicle.hpp"
#include"ItemDatabase.hpp"
#include"Obstacle.hpp"
#include"Camera.hpp"
#include"AnimeAsset.hpp"
#include"EffectManager.hpp"
#include"Menu.hpp"
#include"DebugPoint.hpp"
#include"Boss.hpp"

namespace shimi
{
namespace state
{
class GBState;
}

class GameBase
{
private:
public:
	Texture m_tex;

	//myBalletManager;
	BalletManager m_myBM = BalletManager(this);

	//enemyBalletManager
	BalletManager m_enemyBM = BalletManager(this);

	//EnemyManager
	EnemyManager m_EM = EnemyManager(this);

	MyVehicle m_mv = MyVehicle(this);

	ItemDetabase m_idb;

	std::vector<std::shared_ptr<ObstacleBase>> m_obstacles;

	std::vector<std::shared_ptr<Boss>> m_bosses;

	Menu m_menu;

	std::shared_ptr<state::GBState> m_state;

	GameBase();

	void update()
	{
		m_state->execute(this);
	}

	void mainGameUpdate();

	inline Vec2 getMyVehiclePos()const
	{
		return m_mv.m_pos;
	}

	inline Vec2 getMyVehicleV()const 
	{
		return m_mv.m_v;
	}

	//ƒQ[ƒ€‚ðÅ‰‚ÉŽn‚ß‚éŽž
	void init();

	void updateCamera(const Vec2& cPos)
	{
		D2Camera::I()->m_pos = cPos;
	}

	void collisionPlayerWithEnemy();

	void collisionEnemyWithBallet();

	void collisionBalletWithObstacle();

	void mainGameDraw()const;

	void draw()const;

	void changeState(const std::shared_ptr<state::GBState>& state);

	Optional<Vec2> getNearestEnemyPos()const
	{
		if (!(m_EM.m_enemies.size()==0))
		{
			auto& enemy = std::min_element(m_EM.m_enemies.begin(), m_EM.m_enemies.end(), [this](const std::shared_ptr<Enemy>& a, const std::shared_ptr<Enemy>& b)
			{
				return a->m_pos.distanceFrom(getMyVehiclePos()) < b->m_pos.distanceFrom(getMyVehiclePos());
			});

			return enemy->m_pos;
		}
		else
		{
			return none;
		}
	}

	void collisionPlayerWithBallet();

	template <typename T>
	bool collisionSomethingWithObstacle(const T& shape)
	{
		return AnyOf(m_obstacles, [&shape](const std::shared_ptr<ObstacleBase>& op){return op->m_pols.intersects(shape); });
	}

	void collisionMyBalletWithBreakableObstacle();

	void breakObstacleByTag(const String& tag)
	{
		Erase_if(m_obstacles, [&tag](const std::shared_ptr<ObstacleBase>& o){ return o->m_tag && (o->m_tag.value() == tag); });
	}


#ifdef _DEBUG
	DebugPoint m_debugP;
#endif
};


}