#pragma once
#include<Siv3D.hpp>
#include"Camera.hpp"
#include"ShimiColors.hpp"

namespace shimi
{

class ObstacleBase
{
public:
	ObstacleBase()
	{}

	ObstacleBase(const Vec2& pos, const MultiPolygon& pol, const Optional<String>& tag = none) :
		m_pos(pos),
		m_pols(pol),
		m_tag(tag)
	{}

	virtual bool shotByColor(const Optional<ShimiColors>& col)
	{
		return false;
	}

	Optional<String> m_tag;

	Vec2 m_pos;

	MultiPolygon m_pols;

	virtual void draw()const = 0;

	virtual void drawDebug()const;

	bool m_isDead = false;

};

class Obstacle : public ObstacleBase
{
public:

	Obstacle(){}

	//imagePath����\������_���W�����摜���擾�����̉摜����_���W����Pol�𐶐�
	//�_���W����Pol�͎n�߂Đ�������Ƃ��͉摜����쐬���e�L�X�g�ɕۑ��A2��ڈȍ~�̓e�L�X�g����ǂݍ���
	//�\����ς����ꍇ�̓e�L�X�g�������΍ēx�摜����ǂݍ���
	Obstacle(const Point& pos, const FilePath& imagePath, double simp);

	Texture m_tex;

	void draw()const override
	{
		m_tex.draw(D2Camera::I()->getDrawPos(m_pos));
	}
};


class BreakableObstacle : public ObstacleBase
{
public:

	BreakableObstacle(){}

	BreakableObstacle(const Rect& rect, const ShimiColors& col);

	bool shotByColor(const Optional<ShimiColors>& col)override;

	Rect m_rect;

	ShimiColors m_col;

	void draw()const override;

};


class TriggerBreakableObject : public ObstacleBase
{
public:

	TriggerBreakableObject(){}

	TriggerBreakableObject(const Rect& rect, const String& tag);

	Rect m_rect;

	void draw()const override;

};
}