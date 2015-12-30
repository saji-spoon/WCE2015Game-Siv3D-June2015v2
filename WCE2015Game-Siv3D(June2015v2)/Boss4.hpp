#pragma once
#include<Siv3D.hpp>
#include"Boss.hpp"
#include"Boss4Anime.hpp"
#include"State.hpp"
#include"EnemyShot.hpp"
#include"MyAnime.hpp"
#include"EffectManager.hpp"
#include"Effect.hpp"
#include"PartAnimation.hpp"
#include"State.hpp"
#include"ShimiColors.hpp"

namespace shimi
{
	class GameBase;

	struct BossUnitBase
	{
		GameBase* m_gb;

		ShimiColors m_col;

		std::shared_ptr<EnemyShot> m_shot;

		FrameExp<double> m_flashFrame;

		double m_progress = 0;


		BossUnitBase(){}
		BossUnitBase(GameBase* gb, const Vec2& startPos, const Vec2& endPos, const ShimiColors& col, const std::shared_ptr<EnemyShot>& shot);

		void draw()const;

		void setPath(const Vec2& goal);

		void move(double speed);

		void update();

		inline double getProgressRate()const
		{
			assert((m_endPos - m_startPos).length() != 0);

			return Saturate(m_progress / (m_endPos - m_startPos).length());

		}

		Vec2 m_endPos;
		Vec2 m_startPos;
		Vec2 m_pos;

	};

	struct Boss4BabyBase
	{

		GameBase* m_gb;

		bool m_isFinish = false;

		Boss4BabyBase(){}
		Boss4BabyBase(GameBase* gb);

		virtual void update() = 0;
			/*
		{
			
			if (m_isDead) return;

			m_shot->update(m_pos, Vec2(0, -1));
			m_anime.update();

			m_progress = Saturate(m_progress + 0.1);

			m_pos = EaseInOut(m_startPos, m_endPos, Easing::Cubic, m_progress);
			
		}*/

		virtual void draw()const = 0;

	};


	class Boss4 : public Boss
	{
	public:
		Boss4(GameBase* gb, const Vec2& pos,const std::shared_ptr<state::boss4::Boss4Base>& state = std::shared_ptr<state::boss4::Boss4Base>(new state::boss4::Stay()));

		Boss4Anime m_anime;

		std::shared_ptr<Boss4BabyBase> m_baby;

		//弱点への方向
		std::vector<Vec2> m_weekPs;

		std::shared_ptr<state::boss4::Boss4Base> m_state;

		Rect m_bossArea;

		//何色で攻撃しているのか
		int m_select = 0;

		//ヒットポイント
		int m_life = 5;

		//ダメージ可能か
		bool m_damagable = false;

		double m_theta = 0;

		virtual ~Boss4(){}

		void changeState(const std::shared_ptr<state::boss4::Boss4Base>& newState)
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
			const bool weekPShot = Circle(getWeekPos( static_cast<ShimiColors>(m_select)), 50).intersects(collision);

			if (weekPShot && m_damagable)
			{
				if (m_life >= 1)
				{
					changeState(std::shared_ptr<state::boss4::Boss4Base>(new state::boss4::Damaged()));
				}
				else
				{
					changeState(std::shared_ptr<state::boss4::Boss4Base>(new state::boss4::Vanished()));
				}
				
				return HitState::Damage;
			}

			if (getMyCollision(m_pos).intersects(collision))
			{
				return HitState::NoDamage;
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

		void popBaby(const ShimiColors& col);

		//弱点の絶対位置を求める
		Vec2 getWeekPos(const ShimiColors& col)const;

		void killedSilent() override;

		void setVanish()override
		{
			m_state = std::shared_ptr<state::boss4::Boss4Base>(new state::boss4::Vanished());
		}

	};

}