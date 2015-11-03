#pragma once
#include<Siv3D.hpp>
#include<boost/coroutine/all.hpp>
#include"MyAnime.hpp"
#include"ShimiColors.hpp"
#include"ItemDatabase.hpp"
#include"Config.hpp"
#include"Camera.hpp"
#include"EnemyShot.hpp"
#include"Effect.hpp"


namespace boco = boost::coroutines;

namespace shimi
{
class EnemyManager;
class GameBase;

class Enemy
{
public:
	shimi::MyAnime m_anime;

	std::shared_ptr<EnemyShot> m_shot;

	Vec2 m_pos;

	EnemyManager* m_manager;

	Optional<int> m_itemID=none;

	ShimiColors m_shimiColor;

	int m_depopCount = 0;

	bool m_isDead;

	int m_id = -1;

	Enemy(){}

	//�R���X�g���N�^
	Enemy(EnemyManager* manager,
		const Vec2& pos,
		const shimi::MyAnime& anime,
		const std::shared_ptr<EnemyShot> enemyShot,
		ShimiColors sColor);

	virtual ~Enemy(){}

	//�G�̓����̎���
	virtual void move() = 0;

	virtual void draw()const
	{
		m_anime.drawAt(D2Camera::I()->getDrawPos(m_pos));
	}

	virtual void update();

	virtual inline bool isDead()const
	{
		return m_isDead;
	}

	virtual std::shared_ptr<Enemy> clone() = 0;
};

class StopEnemy : public Enemy
{
public:

	StopEnemy(){}
	StopEnemy(EnemyManager* manager, const Vec2& pos, const shimi::MyAnime& anime, const std::shared_ptr<EnemyShot> enemyShot, ShimiColors sColor)
		:Enemy(manager, pos, anime, enemyShot, sColor)
	{}
	virtual ~StopEnemy(){}

	//�G�̓����̎���
	void move()override;

	std::shared_ptr<Enemy> clone()override
	{
		return std::shared_ptr<Enemy>(new StopEnemy(*this));
	}

};

class StraightEnemy : public Enemy
{
public:
	std::vector<Vec2> m_poss;

	double m_speed;

	//���݂̃X�^�[�g�n�_�ƃS�[���n�_�Ɛi�s�x
	Vec2 m_start;
	Vec2 m_end;
	double m_progress;

	//�n���ꂽ�n�_�\��0�������ʒu�Ƃ��A1�Ɍ�����
	int m_phase = 1;
	int m_indexDir = 1;

	bool m_rotatable;

	bool m_loop;

	bool m_isFinish = false;

	//���x��0�̂Ƃ��O�̌�����ێ�����
	double m_preDir = 0;

	StraightEnemy(){}
	StraightEnemy(EnemyManager* manager,
		std::initializer_list<Vec2> list,
		double speed,
		const shimi::MyAnime& anime,
		const std::shared_ptr<EnemyShot> enemyShot,
		const ShimiColors& sColor,
		bool rotatable = false,
		bool loop = true);

	StraightEnemy(EnemyManager* manager,
		std::vector<Vec2>& poss,
		double speed,
		const shimi::MyAnime& anime,
		const std::shared_ptr<EnemyShot> enemyShot,
		const ShimiColors& sColor,
		bool rotatable = false,
		bool loop = true);
	virtual ~StraightEnemy(){}

	//�G�̓����̎���
	void move()override;

	//start��end��ݒ肵�Aprogress�����Z�b�g
	void setPath(const Vec2& start, const Vec2& end);

	std::shared_ptr<Enemy> clone()override
	{
		return std::shared_ptr<Enemy>(new StraightEnemy(*this));		
	}

	void draw()const override;


};

}