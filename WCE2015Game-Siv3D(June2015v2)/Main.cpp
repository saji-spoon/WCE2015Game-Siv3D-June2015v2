# include <Siv3D.hpp>
#include<algorithm>
#include"Camera.hpp"

namespace shimi{

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

	void draw(const D2Camera& camera)
	{
		m_tex.drawAt(camera.getDrawPos(m_pos));
	}
};

class MyVehicle
{
public:
	Vec2 m_pos = Point(640, 400);

	Vec2 m_v = Circular(3, 0);

	std::vector<Polygon> m_walls;

	Texture m_tex = Texture(L"Maze.png");


public:
	MyVehicle()
	{
		const Polygon pol = Imaging::FindExternalContour(Image(L"Maze.png"), true) + Vec2(320, 240);

		const Polygon pol2 = pol.simplified(10.0);

		const Polygon polRect = Rect(320, 240, 60, 60).asPolygon();

		m_walls.push_back(pol2);

		m_walls.push_back(polRect);

	}

	void collisionPlayerWithObject()
	{
		Vec2 futurePos = m_pos + m_v;//そのままならm_v進める

		const int bodySize = 20;

		std::vector<Line> wallLines;

		for (const auto& wall : m_walls)
		{
			const auto& outer = wall.outer();

			//全ての壁のLineについて、本体の未来位置と交差するものはwallLinesへ
			for (size_t i = 0; i < outer.size(); ++i)
			{
				const Line line(outer[i], outer[(i + 1) % outer.size()]);

				wallLines.push_back(line);
			}
		}

		//リストを、当たり判定円の中心と交差した壁へのclosestの距離が近い順にならべる
		std::sort(wallLines.begin(), wallLines.end(), [&futurePos](const Line& wallA, const Line& wallB)
		{
			return (futurePos - wallA.closest(futurePos)).length() < (futurePos - wallB.closest(futurePos)).length();
		});

		for (int j = 0; j < 2; ++j)
		{
			for (const auto& w : wallLines)
			{
				if (w.intersects(Circle(futurePos, bodySize)))
				{
					const double sink = (bodySize - (futurePos - w.closest(futurePos)).length());

					const Vec2 sinkedDir = (w.closest(futurePos) - futurePos).normalized();

					futurePos -= sinkedDir*sink;

					//Circle(futurePos, 20).drawFrame(2, 0, Palette::Orange);
				}
			}
		}


		m_pos = futurePos;

		if (Input::KeyRight.pressed)
		{
			m_v.rotate(0.08);
		}

		if (Input::KeyLeft.pressed)
		{
			m_v.rotate(-0.08);
		}

	}

	void update()
	{
		collisionPlayerWithObject();
	}

	void draw(const D2Camera& camera)const
	{
		const Vec2 myDrawPos = camera.getDrawPos(m_pos);

		Circle(myDrawPos, 20).drawFrame(0, 3, Palette::Gray);

		Line(myDrawPos, myDrawPos + m_v * 20).draw(3, Palette::Dimgray);

		const Vec2  testObjectPos = camera.getDrawPos({320, 240 });

		m_tex.draw(testObjectPos);

		//.drawAt(320 + m_tex.width / 2, 240 + m_tex.height / 2);

		for (const auto& wall : m_walls)
		{
			wall.drawFrame(camera.getDrawPos({ 0 ,0 }), 2, Color(40, 200, 200, 30));
		}
	}

};

class GameBase
{
private:
public:

	Image m_image = Image(Window::Size(), Palette::White);

	DynamicTexture m_dTex = DynamicTexture(m_image);

	std::vector<Ballet> m_ballets;

	MyVehicle mv;

	D2Camera m_camera;

	GameBase() :m_camera(mv.m_pos)
	{
	}

	void update()
	{
		updateCamera(mv.m_pos);
		
		mv.update();

		if (Mouse::LeftClicked())
		{
			m_ballets.push_back(Ballet(L"ballet.png"));

			Println(Profiler::FPS());
		}

		if (Mouse::RightClicked())
		{
			for (auto& b : m_ballets)
			{
				b.drop(m_image);
				//b.m_image.write(m_image, b.m_pos);
			}

			m_dTex.fill(m_image);
		}

		std::for_each(m_ballets.begin(), m_ballets.end(), [](Ballet& b){ b.update(); });
	}

	void updateCamera(const Vec2& cPos)
	{
		m_camera.m_pos = cPos;
	}

	void draw()
	{
		m_dTex.draw(m_camera.getDrawPos({ 0, 0 }));

		mv.draw(m_camera);

		std::for_each(m_ballets.begin(), m_ballets.end(), [this](Ballet& b){ b.draw(m_camera); });
	}

};

}//名前空間の終わり


void Main()
{
	using namespace shimi;

	Window::Resize(1280, 800);

	GameBase gb;

	while (System::Update())
	{

		gb.draw();

		gb.update();

		if (Input::MouseL.pressed)
		{

		}
	}
}
