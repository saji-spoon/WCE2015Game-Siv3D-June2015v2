#pragma once
#include<Siv3D.hpp>
#include"Camera.hpp"


namespace shimi
{

class BalletManager;

class Ballet
{
public:
	Texture m_tex;

	Image m_image;

	BalletManager* m_manager;

	Vec2 m_pos;

public:

	Ballet(){}

	Ballet(BalletManager* bm, const FilePath& path, const Vec2& pos);

	void update()
	{
		m_pos += Vec2(0, -1);
	}

	void drop(Image& img)
	{
		m_image.write(img, m_pos.asPoint() - m_tex.size / 2, Alpha(128));
	}

	void draw(const D2Camera& camera)const 
	{
		m_tex.drawAt(camera.getDrawPos(m_pos));
	}
};

}