#pragma once
#include<Siv3D.hpp>
#include"MRShotGenerator.hpp"

class MRVehicle
{
public:

	MRVehicle() :interval(0), vehicleType(ShotType::Rotate), sakuraShot(1000), chaseShot(1000)
	{}
	
	void draw()
	{


		Rect(pos() - Point(30, 30), { 60, 60 })(TextureAsset(L"player")).draw();

		switch (vehicleType)
		{
		case MRVehicle::ShotType::Rotate:
			TextureAsset(L"ballet1").draw(pos(), Alpha(180));
			break;
		case MRVehicle::ShotType::Chase:
			TextureAsset(L"ballet2").draw(pos(), Alpha(180));
			break;
		case MRVehicle::ShotType::Sakura:
			TextureAsset(L"ballet3").draw(pos(), Alpha(180));
			break;
		default:
			break;
		}


	}

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

private:
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
};
