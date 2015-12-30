#include"State.hpp"
#include"GameBase.hpp"
#include"Boss.hpp"
#include"EffectManager.hpp"
#include"Effect.hpp"
#include"BGMManager.hpp"
#include"Boss2.hpp"
#include"Effect.hpp"

using namespace shimi;

//MainGameState

void state::MainGame::draw(const GameBase* gb)const
{
	gb->mainGameDraw();
}

void state::MainGame::execute(GameBase* gb)
{
	gb->mainGameUpdate(false, false);
}

void state::Menu::draw(const GameBase* gb)const
{
	gb->mainGameDraw();

	gb->m_menu.draw();
}

void state::Menu::execute(GameBase* gb)
{
	//ゲームのUpdateはせずにメニューのupdateとゲーム・メニューの描画のみ

	gb->m_menu.update();
}

void state::Menu::enter(GameBase* gb)
{
	//m_menuはMenuに切り替わるたびに更新する（m_mvをロードする）
	gb->m_menu = ::shimi::Menu(gb, gb->m_mv);
}

void state::Menu::exit(GameBase* gb)
{
	//上下順に選択した装備をソートしてから
	gb->m_menu.m_mvData.m_shotManager.sortEquipShotWithHierarchy();

	//メニュー画面で変更した装備データを反映
	gb->m_mv.m_shotManager.m_equipShot = gb->m_menu.m_mvData.m_shotManager.m_equipShot;
}

void state::Clear::draw(const GameBase* gb)const
{
	gb->mainGameDraw();
}

void state::Clear::enter(GameBase* gb)
{
	BGMManager::I()->stopBGM();
}

void state::Clear::execute(GameBase* gb)
{
	gb->mainGameUpdate(true, false);

	if (m_timer > 120)
	{
		gb->m_isCleared = true;
	}

	++m_timer;

}

void state::Clear::exit(GameBase* gb)
{
}

void state::Event1::draw(const GameBase* gb)const
{
	gb->mainGameDraw();
}

void state::Event1::enter(GameBase* gb)
{
	m_camera.init();
}

void state::Event1::execute(GameBase* gb)
{
	gb->mainGameUpdate(true, true);

	m_camera.update();

	if (m_timer > 120)
	{
		gb->breakObstacleByTag(L"ToLastBoss");
	}

	if (m_camera.isFinished())
	{
		gb->changeState(std::shared_ptr<GBState>(new MainGame()));
		return;
	}

	++m_timer;

}

void state::Event1::exit(GameBase* gb)
{

}

void state::myvehicle::Normal::enter(MyVehicle& mv)
{
	mv.m_drawable = true;
}

void state::myvehicle::Normal::execute(MyVehicle& mv)
{
	mv.GameUpdate(true, true);
}

void state::myvehicle::Normal::exit(MyVehicle& mv){}

void state::myvehicle::Damaged::enter(MyVehicle& mv)
{
	mv.m_damageEffect = 0.2;

	SoundAsset(L"Damage").play();
}

void state::myvehicle::Damaged::execute(MyVehicle& mv)
{
	mv.GameUpdate(false, true);

	mv.m_damageEffect = m_alpha.getData();

	if (m_damagedTimer <= 0)
	{
		mv.changeState(std::shared_ptr<state::myvehicle::MVState>(new state::myvehicle::Normal()));
		return;
	}

	m_alpha.update();

	--m_damagedTimer;
}

void state::myvehicle::Damaged::exit(MyVehicle& mv)
{
	mv.m_damageEffect = 1.0;
}

void state::myvehicle::Killed::enter(MyVehicle& mv)
{
	EffectManager::I()->effect.add<VanishingMV>(mv.m_pos, 60, Alpha(0));

	SoundAsset(L"GameOver").playMulti();

	mv.m_gb->m_savePoint.setTimer(300);

	mv.m_drawable = false;
}

void state::myvehicle::Killed::execute(MyVehicle& mv)
{
	if (m_timer >= 120)
	{
		mv.changeState(std::shared_ptr<state::myvehicle::MVState>(new state::myvehicle::Starting()));

		return;
	}

	++m_timer;
}

void state::myvehicle::Killed::exit(MyVehicle& mv)
{
	mv.reset();
	mv.recoverPos();
	mv.m_gb->m_EM.popForce(mv.m_pos, ConfigParam::POP_DISTANCE_IN);
}

void state::myvehicle::Starting::enter(MyVehicle& mv)
{
	EffectManager::I()->effect.add<Charging>(mv.m_pos);

	SoundAsset(L"Recover").play();

	mv.m_drawable = false;
}

void state::myvehicle::Starting::execute(MyVehicle& mv)
{
	if (m_timer == 80)
	{
		mv.m_drawable = true;
	}
	else if (m_timer >= 140)
	{
		mv.changeState(std::shared_ptr<state::myvehicle::MVState>(new state::myvehicle::Normal()));
		return;
	}

	++m_timer;
}

void state::myvehicle::Starting::exit(MyVehicle& mv)
{
}

void state::myvehicle::ToBoss::enter(MyVehicle& mv)
{
	mv.m_drawable = false;

	EffectManager::I()->effect.add<BossWarp>(mv.m_pos, 100);

	SoundAsset(L"Warp").playMulti();
}

void state::myvehicle::ToBoss::execute(MyVehicle& mv)
{
	if (m_timer >= 120)
	{
		mv.changeState(std::shared_ptr<state::myvehicle::MVState>(new state::myvehicle::Starting()));

		return;
	}

	++m_timer;
}

void state::myvehicle::ToBoss::exit(MyVehicle& mv)
{
	mv.m_pos = Vec2(750, 9000);

	mv.m_drawable = true;
}

//BossState

void state::boss1::Normal::enter(Boss1& gb)
{
	//ダメージ与えられる
	gb.m_damagable = true;
}

void state::boss1::Normal::execute(Boss1& gb)
{
	if (m_timer <= 80)
	{
		++m_timer;
	}
	else if (!gb.isInBossBattle())
	{
		gb.changeState(std::shared_ptr<Boss1Base>(new Stay()));
		return;
	}
	else
	{
		gb.changeState(std::shared_ptr<Boss1Base>(new Run()));

		return;
	}
}

void state::boss1::Normal::exit(Boss1& gb)
{
	gb.m_damagable = false;
}

void state::boss1::Run::enter(Boss1& gb)
{
	SoundAsset(L"Boss1Voice1").play();

	gb.setVtoMV();
}

void state::boss1::Run::execute(Boss1& gb)
{
	//壁にぶつかっていればfalse
	bool isCompleted = gb.run();

	gb.m_anime.update();

	if (!isCompleted)
	{
		gb.changeState(std::shared_ptr<state::boss1::Boss1Base>(new state::boss1::Normal()));
	}
}

void state::boss1::Run::exit(Boss1& gb)
{
}

void state::boss1::Stay::enter(Boss1& gb)
{
	EffectManager::I()->effect.add<BossWarp>(gb.m_pos, 250);

	BGMManager::I()->changeBGM(L"NormalStage");

	gb.m_v = Vec2(0, -1);
}

void state::boss1::Stay::execute(Boss1& gb)
{
	if (m_timer == 20)
	{
		gb.returnToStayPos();
	}
	else if (m_timer >= 60)
	{
		if (gb.getBossArea().intersects(gb.m_gb->getMyVehiclePos()))
		{
			gb.changeState(std::shared_ptr<state::boss1::Boss1Base>(new Run()));
			return;
		}
	}

	if (m_timer <= 500)
	{
		++m_timer;
	}
}

void state::boss1::Stay::exit(Boss1& gb)
{
	BGMManager::I()->changeBGM(L"BossBattle");
}

void state::boss1::Damaged::enter(Boss1& gb)
{
	gb.m_damagable = false;

	gb.m_anime.m_mode = Boss1AnimeMode::Damaged;
}

void state::boss1::Damaged::execute(Boss1& gb)
{
	if (m_timer <= 120)
	{
		++m_timer;
	}
	else
	{
		gb.changeState(std::shared_ptr<Boss1Base>(new Run()));

		return;
	}
}

void state::boss1::Damaged::exit(Boss1& gb)
{
	gb.m_anime.m_mode = Boss1AnimeMode::Normal;

}

void state::boss1::Vanish::enter(Boss1& gb)
{
	gb.killedSilent();

	SoundAsset(L"BossVanish").playMulti();

	EffectManager::I()->effect.add<BossVanish>(gb.m_pos, 250);

	BGMManager::I()->changeBGM(L"NormalStage");

	gb.m_gb->breakObstacleByTag(L"Boss1Exit");

}

void state::boss1::Vanish::execute(Boss1& gb)
{
}

void state::boss1::Vanish::exit(Boss1& gb){}

void state::boss2::Normal::enter(Boss2& gb)
{
}

void state::boss2::Normal::execute(Boss2& gb)
{
	gb.m_anime.update();

	if (m_timer > 120)
	{
		gb.changeState(std::shared_ptr<state::boss2::Boss2Base>( new state::boss2::Barrier()));
		return;
	}

	++m_timer;
}

void state::boss2::Normal::exit(Boss2& gb){}

void state::boss2::Barrier::enter(Boss2& gb)
{
	SoundAsset(L"FlyBoss").playMulti();
	gb.putBaby();
	gb.m_damagable = false;
	gb.m_barrier = true;
}

void state::boss2::Barrier::execute(Boss2& gb)
{
	gb.m_anime.update();

	for (auto& baby : gb.m_babys)
	{
		baby.update();
	}

	if (!(gb.isInBossBattle()))
	{
		gb.changeState(std::shared_ptr<state::boss2::Boss2Base>(new state::boss2::Stay()));
		return;
	}

	if (AllOf(gb.m_babys, [](const Boss2Baby& baby){ return baby.m_isDead; }))
	{
		gb.changeState(std::shared_ptr<state::boss2::Boss2Base>(new state::boss2::Damagable()));
		return;
	}
}

void state::boss2::Barrier::exit(Boss2& gb)
{
	gb.m_barrier = false;
}

void state::boss2::Damagable::enter(Boss2& gb)
{
	gb.m_damagable = true;
}

void state::boss2::Damagable::execute(Boss2& gb)
{
	if (m_timer > 300)
	{
		gb.changeState(std::shared_ptr<state::boss2::Boss2Base>(new state::boss2::Barrier()));
		return;
	}

	++m_timer;
}

void state::boss2::Damagable::exit(Boss2& gb)
{
	gb.m_damagable = false;
}

void state::boss2::Damaged::enter(Boss2& gb)
{
	gb.m_anime.m_mode = Boss2AnimeMode::Damaged;
}

void state::boss2::Damaged::execute(Boss2& gb)
{
	if (m_timer > 100)
	{
		gb.changeState(std::shared_ptr<state::boss2::Boss2Base>(new state::boss2::Barrier()));
		return;
	}

	++m_timer;
}

void state::boss2::Damaged::exit(Boss2& gb)
{
	gb.m_anime.m_mode = Boss2AnimeMode::Normal;
}

void state::boss2::Vanish::enter(Boss2& gb)
{
	gb.m_gb->m_itemObjects.push_back(gb.m_pos + Vec2(0, 500));

	gb.killedSilent();

	EffectManager::I()->effect.add<BossVanish>(gb.m_pos, 250);

	BGMManager::I()->changeBGM(L"NormalStage");

	SoundAsset(L"BossVanish").playMulti();

	gb.m_gb->breakObstacleByTag(L"Boss2Exit");
}

void state::boss2::Vanish::execute(Boss2& gb)
{
}

void state::boss2::Vanish::exit(Boss2& gb){}

void state::boss2::Stay::enter(Boss2& gb)
{
	gb.killBaby();

	BGMManager::I()->changeBGM(L"NormalStage");
}

void state::boss2::Stay::execute(Boss2& gb)
{
	if (m_timer >= 60)
	{
		if (gb.m_bossArea.m_pols.intersects(Circle(gb.m_gb->getMyVehiclePos(), 10)))
		{
			gb.changeState(std::shared_ptr<state::boss2::Boss2Base>(new Normal()));
			return;
		}
	}

	if (m_timer <= 500)
	{
		++m_timer;
	}
}

void state::boss2::Stay::exit(Boss2& gb)
{
	BGMManager::I()->changeBGM(L"BossBattle");
}
