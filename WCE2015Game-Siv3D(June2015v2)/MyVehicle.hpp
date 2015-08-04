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

	std::vector< std::shared_ptr<ShotGenerator> > shotList;//遅延ショットリスト

	ShotOugi ougiShot;
	ShotChase chaseShot;

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
		case ShotType::Red:
		{
			interval = 10;
			ougiShot.update(m_pos, m_v);
			//遅延ショットは管理リストに入れてupdate()で撃つ
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
		//TODO//弾生成クラスのnewとstart, shotListへの挿入
		interval = 1000;
		break;
		*/
		case ShotType::Green:
			//遅延ショットではないのでここで直接撃つ(update)
			interval = 1000;
			chaseShot.update(m_pos, m_v);
			break;
		case ShotType::Blue:
		{
			//遅延ショットではないのでここで直接撃つ(update)
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

};

}