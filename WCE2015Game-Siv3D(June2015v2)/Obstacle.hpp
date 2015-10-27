#pragma once
#include<Siv3D.hpp>
#include"Camera.hpp"

namespace shimi
{
class Obstacle
{
public:

	Obstacle(){}

	//imagePath����\������_���W�����摜���擾�����̉摜����_���W����Pol�𐶐�
	//�_���W����Pol�͎n�߂Đ�������Ƃ��͉摜����쐬���e�L�X�g�ɕۑ��A2��ڈȍ~�̓e�L�X�g����ǂݍ���
	//�\����ς����ꍇ�̓e�L�X�g�������΍ēx�摜����ǂݍ���
	Obstacle(const Point& pos, const FilePath& imagePath, double simp);

	MultiPolygon m_pols;

	Texture m_tex;

	Point m_pos;

	void draw()const
	{
		m_tex.draw(D2Camera::I()->getDrawPos(m_pos));
	}

	void drawDebug()const;
};

}