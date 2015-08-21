#pragma once
#include<Siv3D.hpp>
#include"Camera.hpp"
#include"ShotGenerator.hpp"
#include"Obstacle.hpp"

namespace shimi
{

class GameBase;

class MyVehicle
{
public:
	Vec2 m_pos = Vec2(760, 2650);

	Circular m_v = Circular(3.0, 0);

	GameBase* m_gb;

	enum class ShotType
	{
		Red,
		//Throw,
		Green,
		Blue,
		NumOfType
	};

	std::vector< std::shared_ptr<ShotGenerator> > shotList;//�x���V���b�g���X�g

	ShotOugi ougiShot;
	ShotChase chaseShot;

	TimerMillisec intervalTimer;//�C���^�[�o���v���p�^�C�}�[

	unsigned int interval;//�C���^�[�o��

	ShotType vehicleType;//���@�̒e�^�C�v

public:
	MyVehicle(GameBase* base);

	void collisionPlayerWithObject();

	void draw()const;

	void shot()
	{
		if (intervalTimer.elapsed() < interval) return;

		intervalTimer.restart();

		switch (vehicleType)
		{
		case ShotType::Red:
		{
			interval = 10;
			ougiShot.update(m_pos, m_v);
			//�x���V���b�g�͊Ǘ����X�g�ɓ����update()�Ō���
			/*
			ShotRound* round = new ShotRound(m_gb, 2000, m_pos);
			round->start();
			shotList.push_back(std::shared_ptr<ShotGenerator>(round));
			interval = 2000;
			*/
			break;
		}
		/*
		case ShotType::Throw:
		//TODO//�e�����N���X��new��start, shotList�ւ̑}��
		interval = 1000;
		break;
		*/
		case ShotType::Green:
			//�x���V���b�g�ł͂Ȃ��̂ł����Œ��ڌ���(update)
			interval = 1000;
			chaseShot.update(m_pos, m_v);
			break;
		case ShotType::Blue:
		{
			//�x���V���b�g�ł͂Ȃ��̂ł����Œ��ڌ���(update)
			interval = 10;
			ougiShot.update(m_pos, m_v);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void update()
	{
		m_v.r = Input::KeyX.pressed? 3.0 : 1.8;

		collisionPlayerWithObject();

		for (auto& s : shotList)
		{
			s->update(m_pos, m_v);
		}

		Erase_if(shotList, [=](const std::shared_ptr<ShotGenerator>& sh){ return sh->isDead; });

		if (Input::MouseL.pressed || Input::KeyZ.pressed)
		{
			shot();
		}

		if (const int wh = Mouse::Wheel() != 0)
		{
			vehicleType = static_cast<ShotType>((static_cast<int>(vehicleType)+wh) % (static_cast<int>(ShotType::NumOfType)));
		}

	}
	void wallDebugDraw()const;
};

}