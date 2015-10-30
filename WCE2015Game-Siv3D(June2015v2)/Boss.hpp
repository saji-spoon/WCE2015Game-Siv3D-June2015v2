#pragma once 
#include<Siv3D.hpp>
#include"State.hpp"
#include"Boss1Anime.hpp"
#include"HitState.hpp"
#include"ShimiColors.hpp"

namespace shimi
{

class GameBase;

class Boss
{
public:

	GameBase* m_gb;

	//自機からのダメージを受ける当たり判定
	Vec2 m_pos;

	Boss(){}

	Boss(GameBase* gb, const Vec2& pos);

	//PlayerAttackとのcollisionで呼ばれる
	virtual HitState damage(const Circle& collision, const Optional<ShimiColors>& col, int value) = 0;

	virtual HitState damage(const Quad& collision, const Optional<ShimiColors>& col, int value) = 0;

	virtual HitState damage(const Vec2& collision, const Optional<ShimiColors>& col, int value) = 0;

	virtual void update() = 0;

	virtual void draw()const = 0;

	virtual void debugDraw()const = 0;

	virtual bool isInBossBattle()const = 0;

	virtual bool isVanished()const = 0;

};

class Boss1 : public Boss
{
public:
	Boss1Anime m_anime;

	std::shared_ptr<state::boss1::Boss1Base> m_state;

	Vec2 m_v = Vec2(0, -1);

	Vec2 m_stayPos;

	//ヒットポイント
	int m_life = 3;

	//ダメージを与えられるかどうか
	bool m_damagable = false;

	Boss1(GameBase* gb, const Vec2& pos, std::shared_ptr<state::boss1::Boss1Base> state = std::shared_ptr<state::boss1::Boss1Base>(new state::boss1::Stay())) :Boss(gb, pos), m_state(state), m_stayPos(pos)
	{
		
	}

	void changeState(std::shared_ptr<state::boss1::Boss1Base> newState)
	{
		m_state->exit(*this);
		m_state = newState;
		m_state->enter(*this);
	}

	inline void returnToStayPos()
	{
		m_pos = m_stayPos;
	}

	void update() override;

	void draw() const override;

	void debugDraw()const override;

	//自機に向けてm_vをセット
	void setVtoMV();

	inline Rect getBossArea()const
	{
		return Rect(Vec2(1082, 3395).asPoint(), (Vec2(1915, 4317) - Vec2(1082, 3395)).asPoint());
	}

	//現在の速度で走る　ぶつかったらfalse
	bool run();

	inline Circle getMyCollision(const Vec2& pos)
	{
		return Circle(pos, 100);
	}

	//ダメージ時の処理
	template<typename T>
	HitState damageImpl(const T& collision, const Optional<ShimiColors>& col, int value)
	{
		if (getMyCollision(m_pos).intersects(collision))
		{
			if (m_damagable)
			{
				--m_life;

				if (m_life > 0)
				{
					changeState(std::shared_ptr<state::boss1::Boss1Base>(new state::boss1::Damaged()));
				}
				else
				{
					changeState(std::shared_ptr<state::boss1::Boss1Base>(new state::boss1::Vanish()));
				}
				
			}

			return m_damagable ? HitState::Damage : HitState::NoDamage;
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

	bool isVanished()const;


	void checkMyVehicleAway();
	
};

};