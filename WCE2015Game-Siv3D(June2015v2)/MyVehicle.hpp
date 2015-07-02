#pragma once
#include<Siv3D.hpp>
#include"Camera.hpp"
#include"MRShotGenerator.hpp"

namespace shimi
{

class GameBase;

class MyVehicle
{
public:
	Vec2 m_pos = Point(640, 400);

	Vec2 m_v = Circular(3, 0);

	//---for prototype
	std::vector<Polygon> m_walls;
	Texture m_tex = Texture(L"Maze.png");
	//---

	GameBase* m_gb;

	enum class ShotType
	{
		Rotate,
		//Throw,
		Chase,
		Sakura,
		NumOfType
	};

	std::vector< std::shared_ptr<MRShotGenerator> > shotList;//�x���V���b�g���X�g

	MRShotSakura sakuraShot;
	MRShotChase chaseShot;

	TimerMillisec intervalTimer;//�C���^�[�o���v���p�^�C�}�[

	unsigned int interval;//�C���^�[�o��

	ShotType vehicleType;//���@�̒e�^�C�v

public:
	MyVehicle(GameBase* base);

	void collisionPlayerWithObject();

	void draw(const D2Camera& camera)const;

	void shot()
	{
		if (intervalTimer.elapsed() < interval) return;

		intervalTimer.restart();

		switch (vehicleType)
		{
		case ShotType::Rotate:
		{
			//�x���V���b�g�͊Ǘ����X�g�ɓ����update()�Ō���
			MRShotRound* round = new MRShotRound(2000, pos());
			round->start();
			shotList.push_back(std::shared_ptr<MRShotGenerator>(round));
			interval = 2000;
			break;
		}
		/*
		case ShotType::Throw:
		//TODO//�e�����N���X��new��start, shotList�ւ̑}��
		interval = 1000;
		break;
		*/
		case ShotType::Chase:
			//�x���V���b�g�ł͂Ȃ��̂ł����Œ��ڌ���(update)
			interval = 1000;
			chaseShot.update(pos());
			break;
		case ShotType::Sakura:
		{
			//�x���V���b�g�ł͂Ȃ��̂ł����Œ��ڌ���(update)
			interval = 10;
			sakuraShot.update(pos());
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void update()
	{
		collisionPlayerWithObject();

		for (auto& s : shotList)
		{
			s->update(pos());
		}

		Erase_if(shotList, [=](const std::shared_ptr<MRShotGenerator>& sh){ return sh->isDead; });

		if (Input::MouseL.pressed)
		{
			shot();
		}

		if (const int wh = Mouse::Wheel() != 0)
		{
			vehicleType = static_cast<ShotType>((static_cast<int>(vehicleType)+wh) % (static_cast<int>(ShotType::NumOfType)));
		}

	}

};

}