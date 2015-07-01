#pragma once
#include<Siv3D.hpp>
#include"Camera.hpp"

namespace shimi
{

class Ballet
{
public:
	Texture m_tex;

	Image m_image;

	Point m_pos = Point(320, 300);

public:

	Ballet(){}

	Ballet(FilePath path) :m_image(path), m_tex(path)
	{

	}

	void update()
	{
		m_pos += Point(0, -1);
	}

	void drop(Image& img)
	{
		m_image.write(img, m_pos - m_tex.size / 2, Alpha(128));
	}

	void draw(const D2Camera& camera)const 
	{
		m_tex.drawAt(camera.getDrawPos(m_pos));
	}
};

}