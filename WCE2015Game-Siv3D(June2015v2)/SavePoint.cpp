#include"SavePoint.hpp"
#include"EffectManager.hpp"
#include"Effect.hpp"
#include"GameBase.hpp"
#include"Camera.hpp"
#include"Save.hpp"

using namespace shimi;

SavePoint::SavePoint(GameBase* gb) :m_gb(gb), m_animeState(60)
{

}

void SavePoint::draw()const
{
	for (auto& pos : m_savePoints)
	{
		Circle(D2Camera::I()->getDrawPos(pos), 20).draw(Color(115, 115, 115));
		Circle(D2Camera::I()->getDrawPos(pos), 30).drawFrame(0, 2.0, Color(115, 115, 115));
	}

	switch (m_animeState.m_state)
	{
	case 0:
		
		break;
	case 1:
	{
		const double progressRate = Saturate( 1.0*m_animeState.m_timer / (1.0*m_animeState.m_stateLimit));

		for (const auto& pos : m_savePoints)
		{
			Circle(D2Camera::I()->getDrawPos(pos), 30 + 20 * progressRate).drawFrame(0.0, 5.0, Color(60, 60, 60, TOUINT(255 * (1.0 - progressRate))));
		}

		break;
	}
	}

}

void SavePoint::update()
{
	if (m_timer > 0)
	{
		--m_timer;
	}

	switch (m_animeState.m_state)
	{
	case 0:
		m_animeState.checkTimerAndGoNextState(60);
		break;
	case 1:

		m_animeState.checkTimerAndGoState0(60);
		break;
	}

	m_animeState.update();
}

bool SavePoint::collisionSavePoint(const Vec2& mvPos)
{
	if (m_timer > 0) return false;

	for (auto& pos : m_savePoints)
	{
		if (Circle(mvPos, 10).intersects(Circle(pos, 30)))
		{
			m_nowRecoverPos = pos;

			Save::I()->save(*m_gb);

			NotifyStr2 str2(L"Saved.", L"", Palette::White, 60, Color(180, 180, 180));

			EffectManager::I()->effect.add<Notify>(m_gb, str2);

			SoundAsset(L"ItemGet").playMulti();

			m_timer = 120;

			return true;

		}
	}

	return false;
}

void SavePoint::setTimer(int value)
{ 
	m_timer = value;
}
