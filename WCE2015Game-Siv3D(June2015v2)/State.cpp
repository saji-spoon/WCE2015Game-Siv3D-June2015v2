#include"State.hpp"
#include"GameBase.hpp"
#include"Boss.hpp"
#include"EffectManager.hpp"
#include"Effect.hpp"
#include"BGMManager.hpp"

using namespace shimi;

void state::MainGame::draw(const GameBase* gb)const
{
	gb->mainGameDraw();
}

void state::MainGame::execute(GameBase* gb)
{
	gb->mainGameUpdate();
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

void state::myvehicle::Normal::execute(MyVehicle& mv)
{
	mv.GameUpdate(true, true);
}

void state::myvehicle::Damaged::enter(MyVehicle& mv)
{
	mv.m_damageEffect = 0.2;
}

void state::myvehicle::Damaged::execute(MyVehicle& mv)
{
	mv.GameUpdate(false, true);

	if (m_damagedTimer <= 0) mv.changeState(std::shared_ptr<state::myvehicle::MVState>(new state::myvehicle::Normal()));

	--m_damagedTimer;
}

void state::myvehicle::Damaged::exit(MyVehicle& mv)
{
	mv.m_damageEffect = 1.0;
}

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
	else if (!gb.getBossArea().intersects(gb.m_gb->getMyVehiclePos()))
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

	if (!isCompleted)
	{
		gb.changeState(std::shared_ptr<state::boss1::Boss1Base>(new state::boss1::Normal()));
	}

	gb.m_anime.update();
}

void state::boss1::Run::exit(Boss1& gb)
{
}

void state::boss1::Stay::enter(Boss1& gb)
{
	EffectManager::I()->effect.add<BossWarp>(gb.m_pos, 250);

	BGMManager::I()->changeBGM(L"NormalStage");

	gb.m_v = Vec2(0, 1);
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
	gb.m_damagable = false;

	EffectManager::I()->effect.add<BossVanish>(gb.m_pos, 250);

	gb.m_anime.m_mode = Boss1AnimeMode::Vanished;

	BGMManager::I()->changeBGM(L"NormalStage");

	gb.m_gb->breakObstacleByTag(L"Boss1Exit");

}

void state::boss1::Vanish::execute(Boss1& gb)
{
}

void state::boss1::Vanish::exit(Boss1& gb){}