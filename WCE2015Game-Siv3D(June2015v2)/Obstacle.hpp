#pragma once
#include<Siv3D.hpp>
#include"Camera.hpp"

namespace shimi
{
class Obstacle
{
public:

	Obstacle(){}

	//imagePathから表示するダンジョン画像を取得かつその画像からダンジョンPolを生成
	//ダンジョンPolは始めて生成するときは画像から作成しテキストに保存、2回目以降はテキストから読み込み
	//構成を変えた場合はテキストを消せば再度画像から読み込む
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