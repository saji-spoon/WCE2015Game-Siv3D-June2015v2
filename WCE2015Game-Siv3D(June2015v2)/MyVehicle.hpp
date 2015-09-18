#pragma once
#include<Siv3D.hpp>
#include"Shot.hpp"
#include"ShotGenerator.hpp"
#include"ItemDatabase.hpp"

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

	TimerMillisec intervalTimer;//インターバル計測用タイマー

	unsigned int interval;//インターバル

	ShotType vehicleType;//自機の弾タイプ

	//Shot管理クラス
	class ShotManager
	{
	public:

		struct ShotProperty
		{
			ShimiColors color;
			int exp = 0;
			int level = 0;
		};

		GameBase* m_gb;

		//装備中のショット
		std::vector<Optional<std::shared_ptr<Shot>>> m_equipShot = std::vector<Optional<std::shared_ptr<Shot>>>(3, none);

		//ショットの成長値とレベル
		std::array<ShotProperty, static_cast<size_t>(ShimiColors::ColorNum)> m_shotPropertys;

		//装備可能数
		int m_equipNum = 1;

		//選択しているショット
		int m_select = 0;


		ShotManager(GameBase* gb);

		void update();

		void draw()const;

		void shot()
		{
			m_equipShot[m_select].value()->shot();
		}

		void event();


		std::shared_ptr<Shot> ShimiColorsToShot(ShimiColors col, int level);

	} m_shotManager;
	

public:
	MyVehicle(GameBase* base);

	void collisionPlayerWithObject();

	void draw()const;

	void drawShotEquip()const
	{
		m_shotManager.draw();
	}

	void shot()
	{
		m_shotManager.shot();
	}


	void update();

	void wallDebugDraw()const;

	inline void addShotExp(const ItemRecord& ir)
	{
		assert(ir.m_color != ShimiColors::ColorNum);

		size_t index = static_cast<size_t>(ir.m_color);

		m_shotManager.m_shotPropertys[index].exp += ir.m_value;
	}
};

}