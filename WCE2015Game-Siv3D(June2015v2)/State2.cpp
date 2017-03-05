#include"State.hpp"
#include"Boss4.hpp"
#include"BGMManager.hpp"
#include"GameBase.hpp"
#include"Boss3.hpp"

using namespace shimi;

void state::boss4::Normal::enter(Boss4& gb)
{
}

void state::boss4::Normal::execute(Boss4& gb)
{
	gb.m_anime.update();

	
	if (m_timer > 120)
	{
		gb.changeState(std::shared_ptr<state::boss4::Boss4Base>(new state::boss4::Attack()));
		return;
	}
	

	++m_timer;
}

void state::boss4::Normal::exit(Boss4& gb){}

void state::boss4::Attack::enter(Boss4& gb)
{
	gb.m_select = Random<int>(0, 4);

	SoundAsset(L"LastBoss").playMulti();

	//色の選択、色に対応したBabyのpop
	gb.popBaby(static_cast<ShimiColors>(gb.m_select));

#ifdef _DEBUG
	Println(ToSString(static_cast<ShimiColors>(gb.m_select)));
#endif
}

void state::boss4::Attack::execute(Boss4& gb)
{
	gb.m_anime.update();

	gb.m_theta += 0.02;

	if (gb.m_baby && gb.m_baby->m_isFinish == true)
	{
		gb.changeState(std::shared_ptr<state::boss4::Boss4Base>(new state::boss4::Damagable()));
		return;
	}
}

void state::boss4::Attack::exit(Boss4& gb){}

void state::boss4::Damagable::enter(Boss4& gb)
{
	SoundAsset(L"LastBoss").playMulti();

	gb.m_damagable = true;
	gb.m_anime.m_mode = Boss4AnimeMode::Damagable;
	gb.m_anime.m_col = static_cast<ShimiColors>(gb.m_select);
}

void state::boss4::Damagable::execute(Boss4& gb)
{
	gb.m_anime.update();

	if (!(gb.isInBossBattle()))
	{
		gb.changeState(std::shared_ptr<state::boss4::Boss4Base>(new state::boss4::Stay()));
		return;
	}

	if (m_timer >= 240)
	{
		gb.changeState(std::shared_ptr<state::boss4::Boss4Base>(new state::boss4::Attack()));
		return;
	}

	++m_timer;
}

void state::boss4::Damagable::exit(Boss4& gb)
{
	gb.m_anime.m_mode = Boss4AnimeMode::Normal;

	gb.m_damagable = false;

	gb.m_baby.reset();
}

void state::boss4::Damaged::enter(Boss4& gb)
{
	gb.m_anime.m_mode = Boss4AnimeMode::Damaged;
	--(gb.m_life);
}

void state::boss4::Damaged::execute(Boss4& gb)
{
	if (m_timer >= 120)
	{
		gb.changeState(std::shared_ptr<state::boss4::Boss4Base>(new state::boss4::Attack()));
		return;
	}

	++m_timer;
}

void state::boss4::Damaged::exit(Boss4& gb)
{
	gb.m_anime.m_mode = Boss4AnimeMode::Normal;
}

void state::boss4::Stay::enter(Boss4& gb)
{
	BGMManager::I()->changeBGM(L"NormalStage");
}

void state::boss4::Stay::execute(Boss4& gb)
{
	if (m_timer >= 60)
	{
		if (gb.m_bossArea.intersects(Circle(gb.m_gb->getMyVehiclePos(), 10)))
		{
			gb.changeState(std::shared_ptr<state::boss4::Boss4Base>(new Normal()));
			return;
		}
		
	}

	if (m_timer <= 500)
	{
		++m_timer;
	}
}

void state::boss4::Stay::exit(Boss4& gb)
{
	BGMManager::I()->changeBGM(L"LastBossBGM");
}

void state::boss4::Vanished::enter(Boss4& gb)
{
	gb.killedSilent();

	EffectManager::I()->effect.add<BossVanish>(gb.m_pos, 250);

	BGMManager::I()->changeBGM(L"NormalStage");

	SoundAsset(L"BossVanish").playMulti();

}

void state::boss4::Vanished::execute(Boss4& gb)
{

}

void state::boss4::Vanished::exit(Boss4& gb)
{
}



void state::boss3::Normal::enter(Boss3& gb)
{
}

void state::boss3::Normal::execute(Boss3& gb)
{
	gb.m_anime.update();

	if (m_timer > 120)
	{
		gb.changeState(std::shared_ptr<state::boss3::Boss3Base>(new state::boss3::Barrier()));
		return;
	}

	++m_timer;
}

void state::boss3::Normal::exit(Boss3& gb){}

void state::boss3::Barrier::enter(Boss3& gb)
{
	SoundAsset(L"SakanaBoss").playMulti();
	gb.m_damagable = false;
	gb.m_barrier = true;
	gb.updateShot();
}

void state::boss3::Barrier::execute(Boss3& gb)
{
	gb.m_anime.update();

	gb.m_shot->update(gb.m_pos, Vec2(0, 1));

	if (!(gb.isInBossBattle()))
	{
		gb.changeState(std::shared_ptr<state::boss3::Boss3Base>(new state::boss3::Stay()));
		return;
	}

	if (gb.m_shot->isFinished())
	{
		gb.changeState(std::shared_ptr<state::boss3::Boss3Base>(new state::boss3::Damagable()));
		return;
	}
}

void state::boss3::Barrier::exit(Boss3& gb)
{
	gb.m_barrier = false;
}

void state::boss3::Damagable::enter(Boss3& gb)
{
	gb.m_damagable = true;
}

void state::boss3::Damagable::execute(Boss3& gb)
{
	if (m_timer > 300)
	{
		gb.changeState(std::shared_ptr<state::boss3::Boss3Base>(new state::boss3::Barrier()));
		return;
	}

	++m_timer;
}

void state::boss3::Damagable::exit(Boss3& gb)
{
	gb.m_damagable = false;
}

void state::boss3::Damaged::enter(Boss3& gb)
{
	--(gb.m_life);

	gb.m_anime.m_mode = Boss3AnimeMode::Damaged;
}

void state::boss3::Damaged::execute(Boss3& gb)
{
	if (m_timer > 100)
	{
		gb.changeState(std::shared_ptr<state::boss3::Boss3Base>(new state::boss3::Barrier()));
		return;
	}

	++m_timer;
}

void state::boss3::Damaged::exit(Boss3& gb)
{
	gb.m_anime.m_mode = Boss3AnimeMode::Normal;
}

void state::boss3::Vanish::enter(Boss3& gb)
{
	gb.killedSilent();

	EffectManager::I()->effect.add<BossVanish>(gb.m_pos, 250);

	BGMManager::I()->changeBGMAtBoss(L"NormalStage");

	SoundAsset(L"BossVanish").playMulti();

	gb.m_gb->breakObstacleByTag(L"Boss3Exit");
}

void state::boss3::Vanish::execute(Boss3& gb)
{
}

void state::boss3::Vanish::exit(Boss3& gb){}

void state::boss3::Stay::enter(Boss3& gb)
{

	BGMManager::I()->changeBGM(L"NormalStage");
}

void state::boss3::Stay::execute(Boss3& gb)
{
	if (m_timer >= 60)
	{
		if (gb.m_bossArea.m_pols.intersects(Circle(gb.m_gb->getMyVehiclePos(), 10)))
		{
			gb.changeState(std::shared_ptr<state::boss3::Boss3Base>(new Normal()));
			return;
		}
	}

	if (m_timer <= 500)
	{
		++m_timer;
	}
}

void state::boss3::Stay::exit(Boss3& gb)
{
	BGMManager::I()->changeBGM(L"BossBattle");
}
