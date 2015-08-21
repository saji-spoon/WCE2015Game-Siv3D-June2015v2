#include"MyVehicle.hpp"
#include"GameBase.hpp"

#define NO_WALLDEBUG 1

using namespace shimi;

MyVehicle::MyVehicle(GameBase* base) :m_gb(base),interval(0), vehicleType(ShotType::Red), ougiShot(base, 1000), chaseShot(base, 1000)
{

}

void MyVehicle::collisionPlayerWithObject()
{
	Vec2 futurePos = m_pos + m_v;//そのままならm_v進める

	const int bodySize = 10;

	std::vector<Line> wallLines;

	for (const auto& obstacle : m_gb->m_obstacles)
	{
		for (const Polygon& wall : obstacle.m_pols)
		{
			const auto& outer = wall.outer();

			//全ての壁のLineについて、wallLinesへ
			for (size_t i = 0; i < outer.size(); ++i)
			{
				const Line line(outer[i], outer[(i + 1) % outer.size()]);

				wallLines.push_back(line);
			}
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
		m_v.theta += 0.08;
	}

	if (Input::KeyLeft.pressed)
	{
		m_v.theta -= 0.08;
	}

}

void MyVehicle::draw()const
{
	for (const auto& o : m_gb->m_obstacles)
	{
		o.draw();
	}
	const Vec2 myDrawPos = D2Camera::I()->getDrawPos(m_pos);

	const double theta = Circular3(m_v).theta;

	TextureAsset(L"Hero").rotate(theta + Pi / 2.0).drawAt(myDrawPos);

	const Vec2  testObjectPos = D2Camera::I()->getDrawPos({ 320, 240 });

#ifdef _DEBUG

	FontAsset(L"Debug").draw(Format(m_pos.asPoint()), D2Camera::I()->getDrawPos(m_pos) + Vec2(0, 20), Palette::Black);

#ifndef NO_WALLDEBUG
	wallDebugDraw();
#endif

#endif
}

void MyVehicle::wallDebugDraw()const
{
	for (const auto& o : m_gb->m_obstacles)
	{
		o.drawDebug();
	}

}

