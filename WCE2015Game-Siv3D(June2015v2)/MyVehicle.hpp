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

	Circular m_v = Circular(3.0, 0);//���x

	GameBase* m_gb;//GameBase

	std::vector< std::shared_ptr<ShotGenerator> > shotList;//�x���V���b�g���X�g

	//�Փ˔���p�ꎞ���X�g
	std::vector<Line> wallLines;

	TimerMillisec intervalTimer;//�C���^�[�o���v���p�^�C�}�[

	unsigned int interval;//�C���^�[�o��

	int life = 3;

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

		//�V���b�g���Ȃɂ��Ȃ��Ƃ��Ɍ���
		WhiteShot m_blankShot;

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

		int getLevel(const ShimiColors& col);

		//���ł�col�F�̑��������Ă��邩�ǂ���
		bool isAlreadyEquiped(const ShimiColors& col);

		//�������V���b�g�������ڏ㉺���Ƀ\�[�g
		void sortEquipShotWithHierarchy();

	} m_shotManager;

	std::shared_ptr<state::myvehicle::MVState> m_state;

	//�_���[�W���ɔ����\������
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