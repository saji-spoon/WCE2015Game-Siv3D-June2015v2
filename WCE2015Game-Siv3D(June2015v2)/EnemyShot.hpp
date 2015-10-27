#pragma once
#include<Siv3D.hpp>
#include"Ballet.hpp"

namespace shimi 
{
class GameBase;

struct Schedule1
{
	Vec2 speed;
	int delay;
};

class EnemyShot
{
public:
	GameBase* m_gb;

	EnemyShot(){}
	EnemyShot(GameBase* gb) :m_gb(gb)
	{
	}

	//updateするとスケジュールに応じて弾が発射される
	virtual void update(const Vec2& pos, const Vec2& v) = 0;

	virtual void reset()
	{
		m_timer = 0;
		m_phase = 0;
	}

	virtual void nextPhase()
	{
		m_timer = 0;
		++m_phase;
	}

	//1Phaseの時間管理用のタイマー
	int m_timer = 0;

	//phase…m_scheduleのどの要素まで進行しているか
	int m_phase = 0;

};

class StraightShot : public EnemyShot
{
public:
	std::vector<Schedule1> m_schedule;

	//このBalletの情報を本に弾を生成
	BalletAVR m_copiedBallet;

	//スケジュールの最後まで行った時ループするか
	bool m_loop;

	StraightShot(GameBase* gb, const std::vector<Schedule1>& schedule, BalletAVR copiedBallet, bool loop) :EnemyShot(gb), m_schedule(schedule), m_copiedBallet(copiedBallet), m_loop(loop)
	{
	}

	void update(const Vec2& pos, const Vec2& v)override;

	void shot(const Vec2& pos, const Vec2& dir);
};

}