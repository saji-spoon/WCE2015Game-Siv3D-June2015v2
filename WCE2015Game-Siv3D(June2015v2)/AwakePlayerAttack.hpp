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
		const bool enemyHit = AnyOf(gb->m_EM.m_enemies, [gb, &collision](const CoEnemy& e)
		{
			const bool f = collision.intersects(Circle(e.m_enemy->m_pos, 30));

			if (f)
			{
				if (!e.m_enemy->m_isDead)
				{
					EffectManager::I()->effect.add<VanishingEnemy>(e.m_enemy->m_pos.asPoint(), 25.0, 0.5);
					SoundAsset(L"EnemyVanish").playMulti();
				}

				e.m_enemy->m_isDead = true;


				if (e.m_enemy->m_itemID && !gb->m_idb.isgot(e.m_enemy->m_itemID.value()))
				{
					EffectManager::I()->effect.add<ItemGet>(gb, e.m_enemy->m_pos);

					const int index = e.m_enemy->m_itemID.value();

					gb->m_mv.addShotExp(gb->m_idb.m_list[index]);

					gb->m_idb.got(index);
				}

			}

			return f;
		});

		const bool bossHit = AnyOf(gb->m_bosses, [gb, &collision, &col, &value](const std::shared_ptr<Boss>& b)
		{
			const HitState hit = b->damage(collision, col, value);// collision.intersects(Circle(e.m_enemy->m_pos, 30));

			return hit != HitState::Avoid;
		});

		return enemyHit || bossHit;
		
	}

	template<typename T>
	bool AwakeEnemyAttack(GameBase* gb, const T& collision, const Optional<ShimiColors>& col, int value)
	{
		//渡された攻撃判定図形と、自機の当たり判定（半径20の円）がぶつかるかどうか検証
		const bool f = collision.intersects(Circle(gb->getMyVehiclePos(), 20));

		//自機の被ダメージフラグをセット
		if (f) gb->m_mv.m_isDamaged = true;

		return f;

	}

}