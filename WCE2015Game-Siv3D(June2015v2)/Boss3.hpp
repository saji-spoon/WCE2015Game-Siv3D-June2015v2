#pragma once
#include<Siv3D.hpp>
#include"Boss.hpp"
#include"Boss3Anime.hpp"
#include"State.hpp"
#include"Obstacle.hpp"
#include"EnemyShot.hpp"
#include"MyAnime.hpp"
#include"EffectManager.hpp"
#include"Effect.hpp"

namespace shimi
{

	class Boss3 : public Boss
	{
	public:
		Boss3Anime m_anime;

		std::shared_ptr<EnemyShot> m_shot;

		std::shared_ptr<state::boss3::Boss3Base> m_state;

		Obstacle m_bossArea;

		//ヒットポイント
		int m_life = 3;

		//ダメージを与えられるかどうか
		bool m_damagable = false;

		//Barrier描画フラグ
		bool m_barrier = false;

		Boss3(GameBase* gb, const Vec2& pos, std::shared_ptr<state::boss3::Boss3Base> state = std::shared_ptr<state::boss3::Boss3Base>(new state::boss3::Stay()));

		virtual ~Boss3(){}

		void changeState(const std::shared_ptr<state::boss3::Boss3Base>& newState)
		{
			m_state->exit(*this);
			m_state = newState;
			m_state->enter(*this);
		}

		void update() override;

		void draw() const override;

		void debugDraw()const override;

		inline Circle getMyCollision(const Vec2& pos)
		{
			return Circle(pos, 100);
		}

		//ダメージ時の処理
		template<typename T>
		HitState damageImpl(const T& collision, const Optional<ShimiColors>& col, int value)
		{
			if (m_isDead) return HitState::Avoid;

			if (getMyCollision(m_pos).intersects(collision))
			{
				const bool dm = m_damagable;

				if (m_damagable)
				{
					--m_life;

					if (m_life > 0)
					{
						changeState(std::shared_ptr<state::boss3::Boss3Base>(new state::boss3::Damaged()));
					}
					else
					{
						changeState(std::shared_ptr<state::boss3::Boss3Base>(new state::boss3::Vanish()));
					}

				}

				return dm ? HitState::Damage : HitState::NoDamage;
			}
			return HitState::Avoid;
		}

		HitState damage(const Circle& collision, const Optional<ShimiColors>& col, int value)override
		{
			return damageImpl(collision, col, value);
		}

		HitState damage(const Quad& collision, const Optional<ShimiColors>& col, int value)override
		{
			return damageImpl(collision, col, value);
		}

		HitState damage(const Vec2& collision, const Optional<ShimiColors>& col, int value)override
		{
			return damageImpl(collision, col, value);
		}

		bool isInBossBattle()const override;

		void drawBarrier()const;

		void updateShot()
		{
			m_shot.reset();

			std::vector<Schedule2> tempSchdl;

			int i = 0;

			tempSchdl.push_back({ 1.0, 360.0, Random(3,12), 100 });

			for (i = 1; i < 15; ++i)
			{
				tempSchdl.push_back({ Random(1.0,3.0), 360.0, Random(3, 12), 30 });
			}

			m_shot = std::shared_ptr<EnemyShot>(new MVAimShot(m_gb, tempSchdl, BalletAVR(nullptr, L"enemyBallet1", ShimiColors::Blue, Vec2(0, 0)), false));

		}

		void killedSilent() override;

		void setVanish()override
		{
			m_state = std::shared_ptr<state::boss3::Boss3Base>(new state::boss3::Vanish());
		}
	};

}