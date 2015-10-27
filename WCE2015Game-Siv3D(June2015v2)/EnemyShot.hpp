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

	//update����ƃX�P�W���[���ɉ����Ēe�����˂����
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

	//1Phase�̎��ԊǗ��p�̃^�C�}�[
	int m_timer = 0;

	//phase�cm_schedule�̂ǂ̗v�f�܂Ői�s���Ă��邩
	int m_phase = 0;

};

class StraightShot : public EnemyShot
{
public:
	std::vector<Schedule1> m_schedule;

	//����Ballet�̏���{�ɒe�𐶐�
	BalletAVR m_copiedBallet;

	//�X�P�W���[���̍Ō�܂ōs���������[�v���邩
	bool m_loop;

	StraightShot(GameBase* gb, const std::vector<Schedule1>& schedule, BalletAVR copiedBallet, bool loop) :EnemyShot(gb), m_schedule(schedule), m_copiedBallet(copiedBallet), m_loop(loop)
	{
	}

	void update(const Vec2& pos, const Vec2& v)override;

	void shot(const Vec2& pos, const Vec2& dir);
};

}