#include"Save.hpp"
#include"GameBase.hpp"
#include"Config.hpp"

using namespace shimi;

bool Save::save(const GameBase& gb, const FilePath& path)
{
	getData(gb);

	TextWriter writer(path);

	writer.writeln(m_save);

#ifdef _DEBUG

	TextWriter writest(L"testSave");

	writest.writeln(m_save.m_mvs);

#endif

	return true;

}

bool Save::load(GameBase& gb, const FilePath& path)
{
	//gbから初期状態のm_saveを取得
	getData(gb);

	//ファイルからm_saveへ読み込み
	bool success = loadSaveData(path);

	if (!success)
	{
		LOG_ERROR(L"セーブデータがありません　セーブデータが以下のPathに新しく作られます。：" + FileSystem::FullPath(path));
		return false;
	}

	gb.m_itemObjects = m_save.m_items;

	for (size_t i = 0; i < gb.m_bosses.size(); ++i)
	{
		if (m_save.m_bossBeated[i])
		{
			//m_isDeadがtrueになる、その他諸々
			gb.m_bosses[i]->setVanish();
			gb.m_bosses[i]->killedSilent();
		}
	}

	for (const auto& tag : m_save.m_brokenObstacles)
	{
		gb.breakObstacleByTag(tag, true);
	}

	gb.m_isDoorOpen = m_save.m_isDoorOpen;

	//gb.m_mv = m_save.m_mv;

	gb.m_mv.load(m_save.m_mvs);

	gb.m_savePoint.m_nowRecoverPos = m_save.m_recoverPos;

	gb.m_EM.popForce(gb.getMyVehiclePos(), ConfigParam::POP_DISTANCE_IN);

	return true;
}

bool Save::getData(const GameBase& gb)
{
	m_save.m_items = gb.m_itemObjects;

	for (size_t i = 0; i < gb.m_bosses.size(); ++i)
	{
		m_save.m_bossBeated[i] = gb.m_bosses[i]->m_isDead;
	}

	m_save.m_brokenObstacles = gb.m_breakedObstacleTag;

	m_save.m_isDoorOpen = gb.m_isDoorOpen;

	//m_save.m_mv = gb.m_mv;

	m_save.m_mvs = gb.m_mv.getSave();

	m_save.m_recoverPos = gb.m_savePoint.m_nowRecoverPos;

	return true;
}

bool Save::loadSaveData(const FilePath& path)
{
	if (!FileSystem::Exists(path))
	{
		return false;
	}

	TextReader reader(path);

#ifdef _DEBUG

	/*
	TextReader readTest(L"testSave");

	m_save.m_mvs = Parse<MyVehicleSave>(readTest.readContents());
	*/

#endif

	m_save = Parse<SaveStruct>(reader.readContents());



	return true;
}
