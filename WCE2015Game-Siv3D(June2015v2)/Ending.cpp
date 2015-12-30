#include"Ending.hpp"
#include"DropManager.hpp"
#include"SimpleState.hpp"
#include"Config.hpp"
using namespace shimi;

#define LINE_NUM 13

StaffRoll::StaffRoll()
	:m_reader(L"Resource/StaffRoll/text.txt"),
	m_strs(LINE_NUM, L"")
{
	nextPage();
}

void StaffRoll::draw()const
{
	int i = 0;
	for (const auto& str : m_strs)
	{
		FontAsset(L"Ending").drawCenter(str, 100 + i * 44);

		++i;
	}

	FontAsset(L"Notify2").draw(L"Press Z Key or A Button");
}

void StaffRoll::nextPage()
{
	if (m_isFinished) return;

	size_t i = 0;

	for (; i < m_strs.size(); ++i)
	{
		const auto line = m_reader.readLine();

		if (!line)
		{
			m_isFinished = true;

			break;
		}

		m_strs[i] = line.value();
	}

	for (; i < m_strs.size(); ++i)
	{
		m_strs[i] = L"";
	}
}


Ending::Ending(const std::vector<std::shared_ptr<ObstacleBase>>& obs)
:m_obstacles(obs)
{
	m_fadeTime = 90;

	m_sceneState = SimpleState(m_fadeTime);
}

void Ending::draw()const
{
	m_tex.map(ConfigParam::SIZE_OF_WORLD + Vec2(800, 600)).draw(D2Camera::I()->getDrawPos({ -800, -600 }), Alpha(70));

	DropManager::I()->draw();

	for (const auto& o : m_obstacles)
	{
		o->endingDraw();
	}
	Rect(1280, 800).draw(Alpha(100)*Palette::Black);

	Rect(1280, 800).draw(Alpha(255.0*m_diffuse)*Palette::Black);

	m_staffRoll.draw();

}

void Ending::update()
{
	const double progress = m_camera.update();

	switch (m_sceneState.m_state)
	{
	case 0:
		//フェードイン
		m_diffuse = 1.0 - Saturate( 1.0 * m_sceneState.m_timer / (1.0 * m_fadeTime));

		m_sceneState.checkTimerAndGoNextState(50);
		break;
	case 1:
		//うつす

		if (progress >= 0.8)
		{
			m_sceneState.nextState(m_fadeTime);
		}
		break;
	case 2:
		//フェードアウト

		m_diffuse = Saturate(1.0 * m_sceneState.m_timer / (1.0 * m_fadeTime));

		if (m_sceneState.m_timer >= m_sceneState.m_stateLimit)
		{
			m_camera.reset();
			m_sceneState.checkTimerAndGoState0(m_fadeTime);
		}
		
		break;
	default:
		break;
	}

	m_sceneState.update();

	if (ConfigParam::KEY_A_CLICKED() && m_staffRoll.m_isFinished)
	{
		System::Exit();
		return;
	}

	if (ConfigParam::KEY_A_CLICKED())
	{
		m_staffRoll.nextPage();
	}

	

}