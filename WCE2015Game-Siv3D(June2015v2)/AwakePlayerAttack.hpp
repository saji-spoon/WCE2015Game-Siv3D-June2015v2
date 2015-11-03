#pragma once
#include<Siv3D.hpp>
#include"EffectManager.hpp"
#include"Effect.hpp"
#include"HitState.hpp"

namespace shimi
{
	class GameBase;

	//collision�`��̎��@���̍U������𔭐�������@�Ԃ����Ă����G�̓_���[�W�������s���@�߂�l�F�Փ˂������ǂ���
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
					EffectManager::I()->effect.add<ItemGet>(gb, e->m_pos, e->m_shimiColor);

					const int index = e->m_itemID.value();

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

		const bool obsHit = AnyOf(gb->m_obstacles, [&collision, &col](const std::shared_ptr<ObstacleBase>& obs)
		{
			const bool isColled = obs->m_pols.intersects(collision);

			const bool isCrashed = obs->shotByColor(col) && isColled;

			if (isCrashed && !obs->m_isDead)
			{
				obs->m_isDead = true;

				//�j��A�j���[�V����
			}

			return isColled;
		});

		return enemyHit || bossHit || obsHit;
		
	}

	template<typename T>
	bool AwakeEnemyAttack(GameBase* gb, const T& collision, const Optional<ShimiColors>& col, int value)
	{
		//�n���ꂽ�U������}�`�ƁA���@�̓����蔻��i���a20�̉~�j���Ԃ��邩�ǂ�������
		const bool f = collision.intersects(Circle(gb->getMyVehiclePos(), 20));

		//���@�̔�_���[�W�t���O���Z�b�g
		if (f) gb->m_mv.m_isDamaged = true;

		return f;

	}

}