#include"MyVehicle.hpp"

using namespace shimi;

MyVehicle::MyVehicle(GameBase* base) :m_gb(base),interval(0), vehicleType(ShotType::Red), ougiShot(base, 1000), chaseShot(base, 1000)
{
	//---for prototype
	const Polygon pol = Imaging::FindExternalContour(Image(L"Maze.png"), true) + Vec2(320, 240);

	const Polygon pol2 = pol.simplified(3.0);

	const Polygon polRect = Rect(320, 240, 60, 60).asPolygon();

	m_walls.push_back(pol2);

	m_walls.push_back(polRect);

	m_walls.push_back(Rect(0, 0, 700, 3000).asPolygon());
	m_walls.push_back(Rect(3300, 0, 700, 3000).asPolygon());
	m_walls.push_back(Rect(0, 0, 4000, 450).asPolygon());
	m_walls.push_back(Rect(0, 3550, 6000, 450).asPolygon());

	const Polygon polTemp = Imaging::FindExternalContour(Image(L"temp.png"), true) + Vec2(1000, 1500);
	m_walls.push_back(polTemp.simplified(10.0));

	//---

}

void MyVehicle::collisionPlayerWithObject()
{
	Vec2 futurePos = m_pos + m_v;//そのままならm_v進める

	const int bodySize = 10;

	std::vector<Line> wallLines;

	for (const auto& wall : m_walls)
	{
		const auto& outer = wall.outer();

		//全ての壁のLineについて、wallLinesへ
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

void MyVehicle::draw(const D2Camera& camera)const
{
	FontAsset(L"Debug").draw(Format(m_pos.asPoint()), camera.getDrawPos( m_pos ) + Vec2(0, 20), Palette::Black);

	const Vec2 myDrawPos = camera.getDrawPos(m_pos);

	const double theta = Circular3(m_v).theta;

	TextureAsset(L"Hero").rotate(theta + Pi / 2.0).drawAt(myDrawPos);

	//Line(myDrawPos, myDrawPos + m_v * 20).draw(3, Palette::Dimgray);

	const Vec2  testObjectPos = camera.getDrawPos({ 320, 240 });

	m_tex.draw(testObjectPos);
	m_tex2.draw(camera.getDrawPos({ 1000, 1500 }));

	//.drawAt(320 + m_tex.width / 2, 240 + m_tex.height / 2);
	/*
	for (const auto& wall : m_walls)
	{
		wall.drawFrame(camera.getDrawPos({ 0, 0 }), 2, Color(40, 200, 200, 30));
	}*/
}
