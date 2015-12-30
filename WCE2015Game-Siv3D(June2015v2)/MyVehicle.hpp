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

struct MyVehicleSave;

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

	int m_life = 3;

	//Drawするかどうか
	bool m_drawable = true;

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

		std::shared_ptr<Shot> ShimiColorsToShot(const ShimiColors& col);

		int getLevel(const ShimiColors& col);

		//すでにcol色の装備をしているかどうか
		bool isAlreadyEquiped(const ShimiColors& col);

		//装備中ショットを見た目上下順にソート
		void sortEquipShotWithHierarchy();

		//装備中のショットを構成はそのままにセットし直す（チャージなどが解除）
		void resetEquipShot();

		std::shared_ptr<Shot> getWhiteShotPtr()
		{
			return std::shared_ptr<Shot>(new WhiteShot(m_gb));
		}


	} m_shotManager;

	std::shared_ptr<state::myvehicle::MVState> m_state;

	//ダメージ時に薄く表示する
	double m_damageEffect = 1.0;


	MyVehicle(GameBase* base);

	void collisionPlayerWithObject();

	void draw()const;

	void drawShotEquip()const
	{
		if (!m_drawable) return;

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

	//ricoverPosをsavePointから取得し移動します　速さは↑方向になります
	void recoverPos();

	//ダメージや弾の各種状態をリセットします
	void reset();

	void warp();

	void addSlot();

	//セーブデータを書き出す
	MyVehicleSave getSave()const;

	//引数で渡されたセーブの情報を読みだす
	bool load(const MyVehicleSave& mvs);

};


/*

template <class Char> // 出力ストリーム
inline std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const MyVehicle& mv)
{
	return os << Char('(') << mv.m_pos << Char(',') << mv.m_shotManager << Char(')');
}

template <class Char> // 入力ストリーム
inline std::basic_istream<Char>& operator >>(std::basic_istream<Char>& is, MyVehicle& mv)
{
	Char unused;
	return is >> unused >> mv.m_pos >> unused >> mv.m_shotManager >> unused;
}


template <class Char> // 出力ストリーム
inline std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const MyVehicle::ShotManager& cl)
{
	os << '(' << cl.m_shotPropertys << ')';

	os << '(' << cl.m_equipNum << ')';

	os << '(';

	for (const auto& sh : cl.m_equipShot)
	{
		if (sh)
		{
			if (sh.value()->m_color)
			{
				os << ToSString(sh.value()->m_color.value());
			}
			else
			{
				os << "White";
			}
		}
		else
		{
			os << "None";
		}

		os << ' ';
	}

	os << ')';

	return os;

}


template <class Char> // 入力ストリーム
inline std::basic_istream<Char>& operator >>(std::basic_istream<Char>& is, MyVehicle::ShotManager& cl)
{
	Char unused;

	is >> unused >> cl.m_shotPropertys >> unused;

	is >> unused >> cl.m_equipNum >> unused;

	is >> unused;

	for (auto& sh : cl.m_equipShot)
	{
		String str;

		is >> str;

		if (str == L"None")
		{
			sh = none;
		}
		else if (str == L"White")
		{
			sh = std::shared_ptr<Shot>(new WhiteShot(cl.m_gb));
		}
		else
		{
			const ShimiColors col = ToShimiColors(str);

			sh = cl.ShimiColorsToShot(col, cl.getLevel(col));
		}
	}

	is >> unused;

	return is;
}
*/

template <class Char> // 出力ストリーム
inline std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const MyVehicle::ShotManager::ShotProperty& cl)
{
	return os << L'(' << cl.color << L',' << cl.level << L',' << cl.exp << L')';
}


template <class Char> // 入力ストリーム
inline std::basic_istream<Char>& operator >>(std::basic_istream<Char>& is, MyVehicle::ShotManager::ShotProperty& cl)
{
	Char unused;

	return is >> unused >> cl.color >> unused >> cl.level >> unused >> cl.exp >> unused;
}



}