#pragma once
#include<Siv3D.hpp>
#include"Boss.hpp"
#include"Boss2Anime.hpp"
#include"State.hpp"
#include"Obstacle.hpp"
#include"EnemyShot.hpp"
#include"MyAnime.hpp"
#include"EffectManager.hpp"
#include"Effect.hpp"
#include"AnimeAsset.hpp"

namespace shimi
{
struct Boss2Baby
{
	std::shared_ptr<EnemyShot> m_shot;

	Vec2 m_endPos;
	Vec2 m_startPos;
	Vec2 m_pos;

	MyAnime m_anime;

	double m_progress = 0;

	bool m_isDead = false;

	Boss2Baby(){}
	Boss2Baby(const Vec2& startPos, const Vec2& locatePos, const std::shared_ptr<EnemyShot>& shot) :
		m_pos(startPos),
		m_startPos(startPos),
		m_endPos(locatePos),
		m_shot(shot)
	{
		m_anime = AnimeAsset::I()->Asset(L"boss2Baby");
	}

	void update()
	{
		if (m_isDead) return;

		m_shot->update(m_pos, Vec2(0,-1));
		m_anime.update();

		m_progress = Saturate(m_progress + 0.1);

		m_pos = EaseInOut(m_startPos, m_endPos, Easing::Cubic, m_progress);
	}

	void draw()const
	{
		if (m_isDead) return;

		m_anime.drawAt(D2Camera::I()->getDrawPos(m_pos));

	}

};

class Boss2 : public Boss
{
public:
	Boss2Anime m_anime;

	std::vector<Boss2Baby> m_babys;

	std::shared_ptr<state::boss2::Boss2Base> m_state;

	Obstacle m_bossArea;

	//ヒットポイント
	int m_life = 3;

	//ダメージを与えられるかどうか
	bool m_damagable = false;

	//Barrier描画フラグ
	bool m_barrier = false;

	Boss2(GameBase* gb, const Vec2& pos, std::shared_ptr<state::boss2::Boss2Base> state = std::shared_ptr<state::boss2::Boss2Base>(new state::boss2::Stay()));

	virtual ~Boss2(){}

	void changeState(const std::shared_ptr<state::boss2::Boss2Base>& newState)
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

		const bool babyShot = AnyOf(m_babys, [this, &collision](Boss2Baby& b)
		{
			const bool shotB = !b.m_isDead && Circle(b.m_pos, 20).intersects(collision);

			if (shotB)
			{
				b.m_isDead = true;
				EffectManager::I()->effect.add<VanishingEnemy>(b.m_pos.asPoint(), 25.0, 0.5, ShimiColors::Orange);
				SoundAsset(L"EnemyVanish").playMulti();
			}

			return shotB;
		});

		if (babyShot)
		{
			return HitState::Damage;
		}

		if (getMyCollision(m_pos).intersects(collision))
		{
			bool dm = m_damagable;

			if (m_damagable)
			{
				--m_life;

				if (m_life > 0)
				{
					changeState(std::shared_ptr<state::boss2::Boss2Base>(new state::boss2::Damaged()));
				}
				else
				{
					changeState(std::shared_ptr<state::boss2::Boss2Base>(new state::boss2::Vanish()));
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

	bool isInBossBattle()const;

	void putBaby();
	
	void killBaby()
	{
		for (auto& baby : m_babys)
		{
			baby.m_isDead = true;
		}
	}

	void drawBarrier()const;

	bool IsBabyAllDead()const
	{
		return AllOf(m_babys, [this](const Boss2Baby& b){ return b.m_isDead; });
	}

	void killedSilent() override;

	void setVanish()override
	{
		m_state = std::shared_ptr<state::boss2::Boss2Base>(new state::boss2::Vanish());
	}

};

}