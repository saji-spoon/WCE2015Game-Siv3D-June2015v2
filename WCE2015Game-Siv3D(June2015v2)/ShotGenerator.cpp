#include"ShotGenerator.hpp"
#include"GameBase.hpp"
using namespace shimi;

void ShotRound::generate(const Vec2& vehiclePos, const Vec2& vehicleV)
{
	if (wait.elapsed() > 10)
	{
		for (int i = 0; i < 4; ++i)
		{
			//EntityManager::GetInstance()->createBallet(std::shared_ptr<Ballet>(new BalletAVR(
			m_gb->m_myBM.m_ballets.push_back(std::shared_ptr<Ballet>(new Ballet(
				&(m_gb->m_myBM),
				L"ballet1",
				vehiclePos
				/*
				0.23,
				(7.0 / 640.0*pos.x + (20.0*i) / 360) * 2 * Pi,
				0.2,
				0.08*/)));
		}
		wait.restart();
	}
}

void ShotSakura::generate(const Vec2& vehiclePos, const Vec2& vehicleV)
{
	if (wait.elapsed() > 10)
	{
		for (int i = 0; i < 5; ++i)
		{
			m_gb->m_myBM.m_ballets.push_back(std::shared_ptr<Ballet>(new BalletAVR(
				&(m_gb->m_myBM),
				L"ballet3",
				vehiclePos,
				0.23,
				(7.0 / 640.0*vehiclePos.x + 0.2*i) * 2 * Pi,
				0.2,
				0.08)));
		}


		wait.restart();
	}
}

void ShotChase::generate(const Vec2& vehiclePos, const Vec2& vehicleV)
{
	const Vec2 target = m_gb->m_mv.m_pos;//‚±‚±‚Å’Ç”ö‚·‚é“GÀ•W‚ğæ“¾

	for (int i = 0; i < 5; ++i)
	{
		const Vec2 balletPos = Circular0(60, 0.05 * i * 2 * Pi) + vehiclePos;

		m_gb->m_myBM.m_ballets.push_back(std::shared_ptr<Ballet>(new BalletAVR(
			&(m_gb->m_myBM),
			L"ballet2", 
			balletPos.asPoint(),
			3.0,
			Circular(target - balletPos).theta - Pi / 2.0,
			0)));
	}

	/*
	for (int i = 0; i < 40; ++i)
	{
		const Vec2 balletPos = Circular0(90, 0.025 * i * 2 * Pi) + vehiclePos;

		m_gb->m_myBM.m_ballets.push_back(std::shared_ptr<Ballet>(new BalletAVR(
			&(m_gb->m_myBM),
			L"ballet2",
			balletPos.asPoint(),
			3.0,
			Circular(target - balletPos).theta - Pi / 2.0,
			0)));
	}*/
}

void ShotOugi::generate(const Vec2& vehiclePos, const Vec2& vehicleV)
{
	if (wait.elapsed() > 100)
	{
		for (int i = 0; i < 3; ++i)
		{
			m_gb->m_myBM.m_ballets.push_back(std::shared_ptr<Ballet>(new BalletAVR(
				&(m_gb->m_myBM),
				L"ballet3",
				vehiclePos,
				5.00,
				Circular3(vehicleV).theta + (i-1) * Pi / 36.0,
				0.0,
				0.0)));
		}


		wait.restart();
	}

}