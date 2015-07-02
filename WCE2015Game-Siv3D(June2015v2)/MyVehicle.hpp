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

	std::vector< std::shared_ptr<MRShotGenerator> > shotList;//遅延ショットリスト

	MRShotSakura sakuraShot;
	MRShotChase chaseShot;

	TimerMillisec intervalTimer;//インターバル計測用タイマー

	unsigned int interval;//インターバル

	ShotType vehicleType;//自機の弾タイプ

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
			//遅延ショットは管理リストに入れてupdate()で撃つ
			MRShotRound* round = new MRShotRound(2000, pos());
			round->start();
			shotList.push_back(std::shared_ptr<MRShotGenerator>(round));
			interval = 2000;
			break;
		}
		/*
		case ShotType::Throw:
		//TODO//弾生成クラスのnewとstart, shotListへの挿入
		interval = 1000;
		break;
		*/
		case ShotType::Chase:
			//遅延ショットではないのでここで直接撃つ(update)
			interval = 1000;
			chaseShot.update(pos());
			break;
		case ShotType::Sakura:
		{
			//遅延ショットではないのでここで直接撃つ(update)
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