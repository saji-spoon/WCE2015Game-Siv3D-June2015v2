#pragma once
#include<algorithm>
#include<Siv3D.hpp>
#include"Shot.hpp"
#include"ShotGenerator.hpp"
#include"ItemDatabase.hpp"
#include"State.hpp"

namespace shimi
{

class GameBase;

class MyVehicle
{
public:
	Vec2 m_pos;

	Circular m_v = Circular(3.0, 0);//速度

	GameBase* m_gb;//GameBase

	std::vector< std::shared_ptr<ShotGenerator> > shotList;//遅延ショットリスト

	//衝突判定用一時リスト
	std::vector<Line> wallLines;

	TimerMillisec intervalTimer;//インターバル計測用タイマー

	unsigned int interval;//インターバル

	int life = 3;

	bool m_isDamaged;//そのフレームでダメージを受けたかのフラグ

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

		//ショットがなにもないときに撃つ
		WhiteShot m_blankShot;

		//装備可能数
		int m_equipNum;

		//選択しているショット
		int m_select = 0;

		ShotManager(GameBase* gb);

		void update();

		void draw(const Vec2& pos, const Vec2& v)const;

		void drawAsPreview(const Vec2& pos, const Vec2& v)const;

		void shot(const Vec2& pos, const Vec2& v);

		void event();

		std::shared_ptr<Shot> ShimiColorsToShot(const ShimiColors& col, int level);

		int getLevel(const ShimiColors& col);

		//すでにcol色の装備をしているかどうか
		bool isAlreadyEquiped(const ShimiColors& col);

		//装備中ショットを見た目上下順にソート
		void sortEquipShotWithHierarchy();

	} m_shotManager;

	std::shared_ptr<state::myvehicle::MVState> m_state;

	//ダメージ時に薄く表示する
	double m_damageEffect = 1.0;

	MyVehicle(GameBase* base);

	void collisionPlayerWithObject();

	void draw()const;

	void drawShotEquip()const
	{
		m_shotManager.draw(m_pos, m_v);
	}

	void drawShotEquipAsPreview()const
	{
		m_shotManager.drawAsPreview(m_pos, m_v);
	}

	void shot()
	{
		m_shotManager.shot(m_pos, m_v);
	}

	void update();

	void controll(bool shotable);

	void GameUpdate(bool damagable, bool shotable);

	void wallDebugDraw()const;

	void shotListUpdate()
	{
		for (auto& s : shotList)
		{
			s->update(m_pos, m_v);
		}

		Erase_if(shotList, [=](const std::shared_ptr<ShotGenerator>& sh){ return sh->isDead(); });
	}

	void changeState(const std::shared_ptr<state::myvehicle::MVState>& state)
	{
		m_state->exit(*this);

		m_state = state;

		m_state->enter(*this);
	}

	void damageUpdate();

	inline void addShotExp(const ItemRecord& ir)
	{
		assert(ir.m_color != ShimiColors::ColorNum);

		size_t index = static_cast<size_t>(ir.m_color);

		m_shotManager.m_shotPropertys[index].exp += ir.m_value;
	}
};

}