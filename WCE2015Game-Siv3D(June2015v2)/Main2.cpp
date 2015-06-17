# include <Siv3D.hpp>

/*
void Main()
{
	const Polygon star = Geometry2D::CreateStar(180, 0, Window::Center());

	while (System::Update())
	{
		const Circle player(Mouse::Pos(), 20);

		star.draw(Palette::Yellow);

		player.draw(Palette::Green);

		if (player.intersects(star))
		{
			const auto& outer = star.outer();

			for (size_t i = 0; i < outer.size(); ++i)
			{
				const Line line(outer[i], outer[(i + 1) % outer.size()]);

				if (line.intersects(player))
				{
					line.draw(3, Palette::Red);

					Circle(line.closest(player.center), 5).draw(Palette::White);
				}
			}
		}
	}
}*/