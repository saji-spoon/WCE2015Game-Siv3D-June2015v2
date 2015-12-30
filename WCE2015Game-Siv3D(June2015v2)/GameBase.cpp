#include "GameBase.hpp"
#include"Effect.hpp"
#include"State.hpp"
#include"AwakePlayerAttack.hpp"
#include"EnemyShot.hpp"
#include"BGMManager.hpp"
#include"Config.hpp"
#include"DropManager.hpp"
#include"Save.hpp"

#define NO_WALLDEBUG

shimi::GameBase::GameBase() :
m_tex(L"Resource/Paper2.png"), m_state(new state::MainGame()), m_menu(this, m_mv)
{
}

template <typename T>
void checkCSVRead(const CSVReader& reader, int i, int j)
{
	const auto& check = reader.getOpt<T>(i, j);

	if (!check)
	{
		Println(L"Error;");
		LOG_ERROR(i, L"行", j, L"列：読み込み失敗");
	}
}

using namespace shimi;

struct DataSheetReader
{
	enum class EnemyType
	{
		Stop,
		Str
	};

	enum class ShotType
	{
		Str,
		MV
	};

	StopEnemy tempStop =
		StopEnemy(nullptr,
		{ 600, 4900.0 },
		AnimeAsset::I()->Asset(L"somDia"),
		std::shared_ptr<EnemyShot>(),
		ShimiColors::Red);

	StraightEnemy tempStrEnemy =
		StraightEnemy(nullptr,
		{ Vec2{ 546, 5423.0 }, Vec2{ 1400, 5423.0 }, Vec2{ 1300, 5023.0 } },
		3.0,
		AnimeAsset::I()->Asset(L"somDia"),
		std::shared_ptr<EnemyShot>(),
		ShimiColors::Red);

	std::vector<Vec2> tempStrPoss;

	Optional<ItemRecord> tempRecord;

	std::shared_ptr<EnemyShot> shotCase;

	std::vector<Schedule1> tempSchdl1;
	std::vector<Schedule2> tempSchdl2;

	bool m_isError = false;

	void setNoError()
	{
		m_isError = false;
	}

	void clearVectors()
	{
		tempSchdl1.clear();
		tempSchdl2.clear();
		tempStrPoss.clear();
	}

	void setStopEnemy(const Vec2& pos, const String& animeTag, const String& colStr, const int itemVal)
	{
		tempStop.m_pos = pos;

		setEnemy(tempStop, animeTag, colStr, itemVal);
	}

	void setStrEnemy(const String& possStr, const double speed, const String& animeTag, const String& colStr, const int itemVal, bool rotatable, bool loop)
	{
		for (const auto& pos : possStr.split(L'+'))
		{
			tempStrPoss.push_back(Parse<Vec2>(pos));
		}

		tempStrEnemy.m_speed = speed;

		setEnemy(tempStrEnemy, animeTag, colStr, itemVal);

		tempStrEnemy.m_rotatable = rotatable;
		tempStrEnemy.m_loop = loop;
	}

	template <typename T>
	void setEnemy(T& enemyType, const String& animeTag, const String& colStr, const int itemVal)
	{
		enemyType.m_anime = AnimeAsset::I()->Asset(animeTag);
		const ShimiColors col = ToShimiColors(colStr);
		enemyType.m_shimiColor = col;

		const int val = itemVal;

		if (val == 0)
		{
			tempRecord = 0;
		}
		else
		{
			tempRecord = ItemRecord(col, val);
		}
	}

	void registerEnemy(EnemyManager* EM, GameBase* gb, const EnemyType& etype, const ShotType& stype, const String& ScheduleStr,
		const String& shotAnimeTag, const String& shotColorStr, const bool shotLoop)
	{
		if (stype == ShotType::Str)
		{
			if (ScheduleStr == L"")
			{
				LOG_DEBUG(L"ScheduleStrが空です：Shotを撃たない敵として登録します。");
				tempSchdl1.clear();

			}

			for (const auto& schdl1 : ScheduleStr.split(L'_'))
			{
				const std::vector<String> schdl1Str = schdl1.split(L'+');

				if (schdl1Str.size() != 2)
				{
					tempSchdl1.clear();
					LOG_ERROR(L"schdl1処理が不正です ScheduleStr = ", ScheduleStr);
					m_isError = true;
					return;
				}

				tempSchdl1.push_back({ Parse<Vec2>(schdl1Str[0]), Parse<int>(schdl1Str[1]) });
			}

			shotCase = std::shared_ptr<EnemyShot>(new StraightShot(
				gb,
				tempSchdl1,
				BalletAVR(nullptr, shotAnimeTag, ToShimiColors(shotColorStr), Vec2(0, 0), 0.0, 0.0),
				shotLoop));
		}
		else
		{
			for (const auto& schdl2 : ScheduleStr.split(L'_'))
			{
				const std::vector<String> schdl2Str = schdl2.split(L'+');

				if (schdl2Str.size() != 4)
				{
					LOG_ERROR(L"schdl2処理が不正です ScheduleStr = ", ScheduleStr);
					m_isError = true;
					return;
				}

				/*	double speed;
				double SectorDegree;
				int num;
				int delay;*/

				tempSchdl2.push_back({ Parse<double>(schdl2Str[0]), Parse<double>(schdl2Str[1]), Parse<int>(schdl2Str[2]), Parse<int>(schdl2Str[3]) });
			}

			shotCase = std::shared_ptr<EnemyShot>(new MVAimShot(
				gb,
				tempSchdl2,
				BalletAVR(nullptr, shotAnimeTag, ToShimiColors(shotColorStr), Vec2(0, 0), 0.0, 0.0),
				shotLoop));
		}


		if (etype == EnemyType::Stop)
		{
			EM->registerEnemy(std::shared_ptr<Enemy>(new StopEnemy(EM, tempStop.m_pos, tempStop.m_anime, shotCase, tempStop.m_shimiColor)), tempRecord);
		}
		else
		{
			EM->registerEnemy(std::shared_ptr<Enemy>(new StraightEnemy(EM, tempStrPoss, tempStrEnemy.m_speed, tempStrEnemy.m_anime, shotCase, tempStrEnemy.m_shimiColor, tempStrEnemy.m_rotatable, tempStrEnemy.m_loop)), tempRecord);
		}
	}



};

void shimi::GameBase::mainGameUpdate(bool ending, bool myVehicleStop)
{
	if (!myVehicleStop) m_mv.update();

	m_EM.pop();

	if (!myVehicleStop) updateCamera(m_mv.m_pos);

	for (auto& boss : m_bosses)
	{
		boss->update();
	}

	for (auto& b : m_myBM.m_ballets)
	{
		b->update();
	}

	for (auto& b : m_enemyBM.m_ballets)
	{
		b->update();
	}

	for (auto& e : m_EM.m_enemies)
	{
		e->update();
	}

	collisionEnemyWithBallet();

	collisionBalletWithObstacle();

	if (!myVehicleStop)
	{
		collisionPlayerWithEnemy();

		collisionPlayerWithBallet();

		collisionItemWithMyVehicle();
	}
	
	if (m_savePoint.collisionSavePoint(m_mv.m_pos))
	{
		m_mv.m_life = 3;
	}

	m_savePoint.update();


	Erase_if(m_myBM.m_ballets, [this](const std::shared_ptr<Ballet>& b){return b->isDead(); });

	//自機から離れすぎた弾は削除される
	Erase_if(m_enemyBM.m_ballets, [this](const std::shared_ptr<Ballet>& b)
	{
		return b->isDead() || (b->m_pos.distanceFrom(getMyVehiclePos()) > 1500);
	});

	Erase_if(m_obstacles, [this](const std::shared_ptr<ObstacleBase>& o){return o->m_isDead; });

	Erase_if(m_itemObjects, [](const ItemObject& item){ return item.m_isDead; });

	EffectManager::I()->effect.update();

	m_EM.depop();

	m_hole.update();

	if (ending) return;

	if ((Input::KeyS | Gamepad(0).button(11)).clicked)
	{
		changeState(std::shared_ptr<state::GBState>(new state::Menu()));
	}

	checkGameClear();

	checkBossDoorOpen();

	if (Circle(m_hole.m_pos, 190).intersects(m_mv.m_pos) && m_mv.m_state->getStateID() != state::myvehicle::MVState::StateID::ToBoss)
	{
		m_mv.warp();
		return;
	}

#ifdef _DEBUG
	m_debugP.update();
#endif
}

void shimi::GameBase::mainGameDraw()const
{
	m_tex.map(ConfigParam::SIZE_OF_WORLD + Vec2(800, 600)).draw(D2Camera::I()->getDrawPos({ -800, -600 }), Alpha(70));

	const Point BossWorldBasePos = Point(0, ConfigParam::SIZE_OF_NORMALWORLD.y + ConfigParam::SIZE_OF_WORLDMARGIN.y * 2);

	Rect(D2Camera::I()->getDrawPos(BossWorldBasePos).asPoint(), ConfigParam::SIZE_OF_BOSSWORLD).draw(Palette::Black);

	m_tex.map(ConfigParam::SIZE_OF_BOSSWORLD).draw(D2Camera::I()->getDrawPos(BossWorldBasePos), Color(255,255,255,70));

	DropManager::I()->draw();

	m_savePoint.draw();

	m_mv.draw();

	for (auto& boss : m_bosses)
	{
		boss->draw();
	}

	for (const auto& o : m_obstacles)
	{
		o->draw();
	}

	for (const auto& e : m_EM.m_enemies)
	{
		e->draw();
	}

	for (const auto& b : m_myBM.m_ballets)
	{
		b->draw();
	}

	for (const auto& b : m_enemyBM.m_ballets)
	{
		b->draw();
	}

	for (const auto& item : m_itemObjects)
	{
		item.draw();
	}

	m_hole.draw();

  	m_mv.drawShotEquip();

	
#ifdef _DEBUG
	//m_idb.debug();

	FontAsset(L"Debug").draw(Format(m_mv.m_pos.asPoint()), D2Camera::I()->getDrawPos(m_mv.m_pos), Palette::Black);

	FontAsset(L"Debug").draw(Format(DropManager::I()->m_drops.size()), { 0.0, 100.0 }, Palette::Black);

	m_debugP.draw();

	FontAsset(L"Debug").draw(L"enemyBallets:"+Format(m_enemyBM.m_ballets.size()), Vec2(240, 100), Palette::Black);
	FontAsset(L"Debug").draw(L"enemy:" + Format(m_EM.m_enemies.size()), Vec2(240, 120), Palette::Black);
	FontAsset(L"Debug").draw(L"myBallets:" + Format(m_myBM.m_ballets.size()), Vec2(240, 120), Palette::Black);

	/*
	for(const auto& e : m_EM.m_enemyDatabase)
	{
		++i;

		FontAsset(L"Debug").draw(Format(i, L":", ToSString( e.m_data->m_shimiColor), e.m_isPop), { 240.0, 100.0+i*20 }, Palette::Black);

		e.m_isPop;
	}

	for (const auto& b : m_bosses)
	{
		b->debugDraw();
	}
	*/

#ifndef NO_WALLDEBUG

	for (const auto& o : m_obstacles)
	{
		o->drawDebug();
	}
#endif
#endif 

}

void shimi::GameBase::draw()const
{
	m_state->draw(this);
}

void shimi::GameBase::collisionBalletWithObstacle()
{
	//自分の弾の衝突
	for (const auto& b : m_myBM.m_ballets)
	{
		bool col = collisionSomethingWithObstacle(Circle(b->m_pos, 5)) && !(b->m_shimiColor && b->m_shimiColor == ShimiColors::Purple);

		if (col)
		{
			b->m_isDead = true;

			EffectManager::I()->effect.add<VanishingBallet>(b->m_pos.asPoint(), 13, 0.5);

		}

	}

	//敵の弾の衝突
	for (const auto& b : m_enemyBM.m_ballets)
	{
		bool col = collisionSomethingWithObstacle(Circle(b->m_pos, 5));

		//もしbとeが衝突していたら
		if (col)
		{
			b->m_isDead = true;

			EffectManager::I()->effect.add<VanishingBallet>(b->m_pos.asPoint(), 13, 0.5);

		}
	}


}

void shimi::GameBase::collisionEnemyWithBallet()
{
	for (const auto& b : m_myBM.m_ballets)
	{
		const bool isHit = AwakePlayerAttack(this, Circle(b->m_pos, 5), b->m_shimiColor, 20);

		if (isHit && !b->m_isDead)
		{
			EffectManager::I()->effect.add<VanishingBallet>(b->m_pos.asPoint(), 13, 0.5);

			b->m_isDead = true;
		}
	}

	/*
	Erase_if(m_myBM.m_ballets, [&](const std::shared_ptr<Ballet>& b)
	{
		const bool isHit = AwakePlayerAttack(this, Circle(b->m_pos, 5), b->m_shimiColor, 20);

		if (isHit) EffectManager::I()->effect.add<VanishingBallet>(b->m_pos.asPoint(), 13, 0.5);

		return isHit;
	});
	*/
}

void shimi::GameBase::collisionPlayerWithBallet()
{
	Erase_if(m_enemyBM.m_ballets, [&](const std::shared_ptr<Ballet>& b)
	{
		const bool isHit = AwakeEnemyAttack(this, b->m_pos, b->m_shimiColor, 20);

		return isHit;
	});
}

void shimi::GameBase::collisionPlayerWithEnemy()
{
	for (const auto& e : m_EM.m_enemies)
	{
		AwakeEnemyAttack(this, Circle(e->m_pos, 20), e->m_shimiColor, 1);
	}

	/*
	if (AnyOf(m_EM.m_enemies, [this](const CoEnemy& e){ return e.m_enemy->m_pos.distanceFrom(m_mv.m_pos) < 20; }))
	{
		//Println(L"Attacked!");
	}*/
}

void shimi::GameBase::collisionItemWithMyVehicle()
{
	for (auto& item : m_itemObjects)
	{
		if (Circle(m_mv.m_pos, 10).intersects(item.getCollision()) && !item.m_isDead)
		{
			const NotifyStr2 notify(L"+1", L"Slot", Palette::White, 120, Color(180,180,180));
			EffectManager::I()->effect.add<Notify>(this, notify);

			SoundAsset(L"ItemGet").playMulti();

			item.m_isDead = true;
			m_mv.addSlot();
		}
	}
}

void shimi::GameBase::changeState(const std::shared_ptr<state::GBState>& state)
{
	m_state->exit(this);
	m_state = state;
	m_state->enter(this);
}

void shimi::GameBase::readEnemyData(const FilePath& path)
{

	CSVReader reader(path); 

	if (!reader)
	{
		LOG_DEBUG(L"CSVファイル読み込み失敗");
	}

	DataSheetReader dsr;

	for (int i = 0; i<reader.rows; ++i)
	{
		LOG_DEBUG(L"ReadEnemyData:Line ", i);

		dsr.clearVectors();

		const String type = reader.get<String>(i, 0);

		if (type == L"Enemy")
		{
			const String enemyType = reader.get<String>(i, 1);

			if (enemyType == L"Stop")
			{
				dsr.setStopEnemy(reader.get<Vec2>(i, 2), reader.get<String>(i, 4), reader.get<String>(i, 5), reader.get<int>(i, 6));
#ifdef _DEBUG
				checkCSVRead<Vec2>(reader, i, 2);
				checkCSVRead<String>(reader, i, 4);
				checkCSVRead<String>(reader, i, 5);
				checkCSVRead<int>(reader, i, 6);
#endif

			}
			else if (enemyType == L"Str")
			{
				dsr.setStrEnemy(reader.get<String>(i, 2),
					reader.get<double>(i, 3),
					reader.get<String>(i, 4),
					reader.get<String>(i, 5),
					reader.get<int>(i, 6),
					reader.get<bool>(i, 7),
					reader.get<bool>(i, 8));

#ifdef _DEBUG
				checkCSVRead<Vec2>(reader, i, 2);
				checkCSVRead<double>(reader, i, 3);
				checkCSVRead<String>(reader, i, 4);
				checkCSVRead<String>(reader, i, 5);
				checkCSVRead<int>(reader, i, 6);
				checkCSVRead<bool>(reader, i, 7);
				checkCSVRead<bool>(reader, i, 8);
#endif	
			}
			else
			{
				LOG_ERROR(L"データが不正です：EnemyがStopでもStrでもありません");
				continue;
			}

			int enemyIndex = i;

			++i;

			if (!(i<reader.rows))
			{
				LOG_ERROR(L"データファイルが途中で終了しています");
				continue;
			}

			if (reader.get<String>(i, 0) == L"Ballet")
			{
				DataSheetReader::EnemyType etype;

				DataSheetReader::ShotType stype;

				const String balletType = reader.get<String>(i, 1);

				if (balletType == L"Str")
				{
					stype = DataSheetReader::ShotType::Str;
				}
				else if (balletType == L"MV")
				{
					stype = DataSheetReader::ShotType::MV;
				}
				else
				{
					LOG_ERROR(L"データが不正です：BalletにStrかMVが設定されていません");
					continue;
				}


				if (enemyType == L"Stop")
				{
					etype = DataSheetReader::EnemyType::Stop;
				}
				else
				{
					etype = DataSheetReader::EnemyType::Str;
				}

				dsr.registerEnemy(&m_EM, this, etype, stype, reader.get<String>(i, 2), reader.get<String>(i, 3), reader.get<String>(i, 4), reader.get<bool>(i, 5));
#ifdef _DEBUG
				checkCSVRead<String>(reader, i, 2);
				checkCSVRead<String>(reader, i, 3);
				checkCSVRead<String>(reader, i, 4);
				checkCSVRead<bool>(reader, i, 5);
				LOG_DEBUG(i, L"行:", balletType, L":");
				for (auto& c : reader.get<String>(i, 2).split(L'_'))
				{
					LOG_DEBUG(c);
				}
#endif

				++i;

				for (; i < reader.rows && reader.get<String>(i, 0) == L"Diff"; ++i)
				{
					dsr.clearVectors();

					if (etype == DataSheetReader::EnemyType::Stop)
					{
						dsr.setStopEnemy(reader.get<Vec2>(i, 1), reader.get<String>(enemyIndex, 4), reader.get<String>(enemyIndex, 5), reader.get<int>(i, 2));
					}
					else
					{
						dsr.setStrEnemy(reader.get<String>(i, 1), reader.get<double>(enemyIndex, 3), reader.get<String>(enemyIndex, 4), reader.get<String>(enemyIndex, 5), reader.get<int>(i, 2), reader.get<bool>(enemyIndex, 7), reader.get<bool>(enemyIndex, 8));
					}

					const String shotType = reader.get<String>(i, 3);

					if (shotType == L"Str")
					{
						dsr.registerEnemy(&m_EM, this, etype, DataSheetReader::ShotType::Str, reader.get<String>(i, 4), reader.get<String>(enemyIndex + 1, 3), reader.get<String>(enemyIndex + 1, 4), reader.get<bool>(i, 5));
					}
					else if (shotType == L"MV")
					{
						dsr.registerEnemy(&m_EM, this, etype, DataSheetReader::ShotType::MV, reader.get<String>(i, 4), reader.get<String>(enemyIndex + 1, 3), reader.get<String>(enemyIndex + 1, 4), reader.get<bool>(i, 5));
					}
				}

				--i;

			}

		}
		else
		{
			LOG_ERROR(L"データが不正です:Enemyではありません");
			continue;
		}

	}
};


void shimi::GameBase::checkGameClear()
{
	//すべてのボスを倒したらクリア

#ifdef _DEBUG
	const bool clearTrigger = Mouse::RightClicked();
#else
	const bool clearTrigger = AllOf(m_bosses, [](const std::shared_ptr<Boss>& b)
	{
		return b->m_isDead;
	});
#endif

	if (clearTrigger)
	{
		changeState(std::shared_ptr<state::GBState>(new state::Clear()));
	}
}

void shimi::GameBase::checkBossDoorOpen()
{
	bool f = true;

	for (size_t i = 0; i < m_bosses.size() - 1; ++i)
	{
		f = f && m_bosses[i]->m_isDead;
	}

#ifdef _DEBUG
	const bool openTrigger = Mouse::LeftClicked();
#else
	const bool openTrigger = f;
#endif

	if (openTrigger && !(m_isDoorOpen))
	{
		m_isDoorOpen = true;
		changeState(std::shared_ptr<state::GBState>(new state::Event1()));
	}
	//一度開けたら開けないようにする
}

void shimi::GameBase::breakObstacleByTag(const String& tag, bool silent)
{
	for (auto& obs : m_obstacles)
	{
		if (obs->m_tag && (obs->m_tag.value() == tag))
		{
			m_breakedObstacleTag.push_back(obs->m_tag.value());
			obs->m_isDead = true;
			if (silent) continue;
			EffectManager::I()->effect.add<Vanishing>(obs->m_pols.boundingRect.center, 100, Color(80, 80, 80));
			SoundAsset(L"BreakObstacle").playMulti();
		}
	}
}