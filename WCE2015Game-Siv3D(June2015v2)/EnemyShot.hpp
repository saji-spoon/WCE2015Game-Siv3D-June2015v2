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

struct Schedule2
{
	double speed;

	double SectorDegree;

	int num;

	int delay;
};

class EnemyShot
{
public:
	GameBase* m_gb;

	EnemyShot(){}
	EnemyShot(GameBase* gb, bool loop) :m_gb(gb), m_loop(loop)
	{
	}
	virtual ~EnemyShot(){}

	//update����ƃX�P�W���[���ɉ����Ēe�����˂����
	virtual void update(const Vec2& pos, const Vec2& v) = 0;

	virtual bool isFinished()const = 0;

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

	//1Phase�̎��ԊǗ��p�̃^�C�}�[
	int m_timer = 0;

	//phase�cm_schedule�̂ǂ̗v�f�܂Ői�s���Ă��邩
	int m_phase = 0;

	bool m_loop;

};

class StraightShot : public EnemyShot
{
public:
	std::vector<Schedule1> m_schedule;

	//����Ballet�̏���{�ɒe�𐶐�
	BalletAVR m_copiedBallet;


	StraightShot(GameBase* gb, const std::vector<Schedule1>& schedule, BalletAVR copiedBallet, bool loop) :EnemyShot(gb, loop), m_schedule(schedule), m_copiedBallet(copiedBallet)
	{
	}
	virtual ~StraightShot(){}

	bool isFinished()const override
	{
		return !m_loop && (m_phase >= static_cast<int>(m_schedule.size()));
	}

	void update(const Vec2& pos, const Vec2& v)override;

	void shot(const Vec2& pos, const Vec2& dir);
};

class MVAimShot : public EnemyShot
{

public:
	std::vector<Schedule2> m_schedule;

	//����Ballet�̏���{�ɒe�𐶐�
	BalletAVR m_copiedBallet;

	MVAimShot(GameBase* gb, const std::vector<Schedule2>& schedule, BalletAVR copiedBallet, bool loop) :EnemyShot(gb, loop), m_schedule(schedule), m_copiedBallet(copiedBallet)
	{
	}

	virtual ~MVAimShot(){}

	void update(const Vec2& pos, const Vec2& v)override;

	//theta�x�̐�`�Ɏ��@�_���e��num����
	//theta�͓x���@�ŁI
	void shot(const Vec2& pos, double dosuu, double speed, int num);

	bool isFinished()const override
	{
		return !m_loop && (m_phase >= static_cast<int>(m_schedule.size()));
	}
};
}