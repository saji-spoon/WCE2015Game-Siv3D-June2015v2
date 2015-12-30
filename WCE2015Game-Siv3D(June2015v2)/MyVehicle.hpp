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

	Circular m_v = Circular(3.0, 0);//���x

	GameBase* m_gb;//GameBase

	std::vector< std::shared_ptr<ShotGenerator> > shotList;//�x���V���b�g���X�g

	//�Փ˔���p�ꎞ���X�g
	std::vector<Line> wallLines;

	TimerMillisec intervalTimer;//�C���^�[�o���v���p�^�C�}�[

	unsigned int interval;//�C���^�[�o��

	int m_life = 3;

	//Draw���邩�ǂ���
	bool m_drawable = true;

	bool m_isDamaged;//���̃t���[���Ń_���[�W���󂯂����̃t���O


	//Shot�Ǘ��N���X
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

		//�������̃V���b�g
		std::vector<Optional<std::shared_ptr<Shot>>> m_equipShot = std::vector<Optional<std::shared_ptr<Shot>>>(3, none);

		//�V���b�g�̐����l�ƃ��x��
		std::array<ShotProperty, static_cast<size_t>(ShimiColors::ColorNum)> m_shotPropertys;

		//�����\��
		int m_equipNum;

		//�I�����Ă���V���b�g
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

		//���ł�col�F�̑��������Ă��邩�ǂ���
		bool isAlreadyEquiped(const ShimiColors& col);

		//�������V���b�g�������ڏ㉺���Ƀ\�[�g
		void sortEquipShotWithHierarchy();

		//�������̃V���b�g���\���͂��̂܂܂ɃZ�b�g�������i�`���[�W�Ȃǂ������j
		void resetEquipShot();

		std::shared_ptr<Shot> getWhiteShotPtr()
		{
			return std::shared_ptr<Shot>(new WhiteShot(m_gb));
		}


	} m_shotManager;

	std::shared_ptr<state::myvehicle::MVState> m_state;

	//�_���[�W���ɔ����\������
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

	//ricoverPos��savePoint����擾���ړ����܂��@�����́������ɂȂ�܂�
	void recoverPos();

	//�_���[�W��e�̊e���Ԃ����Z�b�g���܂�
	void reset();

	void warp();

	void addSlot();

	//�Z�[�u�f�[�^�������o��
	MyVehicleSave getSave()const;

	//�����œn���ꂽ�Z�[�u�̏���ǂ݂���
	bool load(const MyVehicleSave& mvs);

};


/*

template <class Char> // �o�̓X�g���[��
inline std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const MyVehicle& mv)
{
	return os << Char('(') << mv.m_pos << Char(',') << mv.m_shotManager << Char(')');
}

template <class Char> // ���̓X�g���[��
inline std::basic_istream<Char>& operator >>(std::basic_istream<Char>& is, MyVehicle& mv)
{
	Char unused;
	return is >> unused >> mv.m_pos >> unused >> mv.m_shotManager >> unused;
}


template <class Char> // �o�̓X�g���[��
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


template <class Char> // ���̓X�g���[��
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

template <class Char> // �o�̓X�g���[��
inline std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const MyVehicle::ShotManager::ShotProperty& cl)
{
	return os << L'(' << cl.color << L',' << cl.level << L',' << cl.exp << L')';
}


template <class Char> // ���̓X�g���[��
inline std::basic_istream<Char>& operator >>(std::basic_istream<Char>& is, MyVehicle::ShotManager::ShotProperty& cl)
{
	Char unused;

	return is >> unused >> cl.color >> unused >> cl.level >> unused >> cl.exp >> unused;
}



}