#include "GameBase.hpp"
#include "Ballet.hpp"

using namespace shimi;

void GameBase::update()
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

void GameBase::draw()const
{
	m_dTex.draw(m_camera.getDrawPos({ 0, 0 }));

	mv.draw(m_camera);

	std::for_each(m_ballets.begin(), m_ballets.end(), [this](const Ballet& b){ b.draw(m_camera); });
}