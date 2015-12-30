#pragma once
#include<Siv3D.hpp>
#include"EffectManager.hpp"
#include"Effect.hpp"
#include"HitState.hpp"

namespace shimi
{
	class GameBase;

	//collision形状の自機側の攻撃判定を発生させる　ぶつかっていた敵はダメージ処理を行う　戻り値：衝突したかどうか
	template<typename T>
	bool AwakePlayerAttack(GameBase* gb, const T& collision, const Optional<ShimiColors>& col, int value)
	{		
		const bool enemyHit = AnyOf(gb->m_EM.m_enemies, [gb, &collision](const std::shared_ptr<Enemy>& e)
		{
			const bool f = collision.intersects(Circle(e->m_pos, 30));

			if (f)
			{
				if (!e->m_isDead)
				{
					EffectManager::I()->effect.add<VanishingEnemy>(e->m_pos.asPoint(), 25.0, 0.5, e->m_shimiColor);
					SoundAsset(L"EnemyVanish").playMulti();
				}

				e->m_isDead = true;


				if (e->m_itemID && !gb->m_idb.isgot(e->m_itemID.value()))
				{
					

					const int index = e->m_itemID.value();

					const int itemVal = gb->m_idb.m_list[index].m_value;
					const ShimiColors itemCol = gb->m_idb.m_list[index].m_color;

					gb->m_mv.addShotExp(gb->m_idb.m_list[index]);

					EffectManager::I()->effect.add<ItemGet>(gb, e->m_pos, itemCol, itemVal);

					gb->m_idb.got(index);
				}

			}

			return f;
		});

		const bool bossHit = AnyOf(gb->m_bosses, [gb, &collision, &col, &value](const std::shared_ptr<Boss>& b)
		{
			const HitState hit = b->damage(collision, col, value);// collision.intersects(Circle(e.m_enemy->m_pos, 30));

			switch (hit)
			{
			case HitState::Damage:
				SoundAsset(L"BossDamage").playMulti();
				break;
			case HitState::NoDamage:
				SoundAsset(L"BossNoDamage").play();
				break;
			default:
				break;
			}

			return hit != HitState::Avoid;
		});

		const bool obsHit = AnyOf(gb->m_obstacles, [&collision, &col](const std::shared_ptr<ObstacleBase>& obs)
		{
			const bool isColled = obs->m_pols.intersects(collision);

			const bool isCrashed = obs->shotByColor(col) && isColled;

			if (isCrashed && !obs->m_isDead)
			{
				SoundAsset(L"BreakObstacle").playMulti();

				obs->m_isDead = true;

				EffectManager::I()->effect.add<Vanishing>(obs->m_pols.boundingRect.center, 100, ToColor(col.value()));

				
			}

			return isCrashed;
		});

		return enemyHit || bossHit || obsHit;
		
	}

	template<typename T>
	bool AwakeEnemyAttack(GameBase* gb, const T& collision, const Optional<ShimiColors>& col, int value)
	{
		//渡された攻撃判定図形と、自機の当たり判定（半径20の円）がぶつかるかどうか検証
		const bool f = collision.intersects(Circle(gb->getMyVehiclePos(), 20));

		//自機の被ダメージフラグをセット
		if (f && !(gb->m_mv.m_isDamaged))
		{
			gb->m_mv.m_isDamaged = true;
		}

		return f;

	}

}