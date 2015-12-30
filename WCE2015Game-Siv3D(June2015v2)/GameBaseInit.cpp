#include"GameBase.hpp"
#include"EnemyShot.hpp"
#include"BGMManager.hpp"
#include"Boss2.hpp"
#include"Boss3.hpp"
#include"Boss4.hpp"
using namespace shimi;

void shimi::GameBase::init()
{
	readEnemyData(L"Resource/Data/test3.csv");

	//Stage
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new Obstacle({ 0, 0 }, L"Resource/Stage/stage_beehive.png", 12.0)));
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new Obstacle({ 62, 3176 }, L"Resource/Stage/stage_start.png", 12.0)));
	
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new Obstacle(Point{ 1757, 0 }*2, L"Resource/Stage/stage_planet.png", 12.0)));
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new Obstacle(Point{ 1311, 1454 }*2, L"Resource/Stage/stage_crystal.png", 12.0)));
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new Obstacle(Point{ 1002, 1551 }*2, L"Resource/Stage/stage_fish_and_vine.png", 12.0)));
	
	//BreakableObstacle
	
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new BreakableObstacle(Point(972, 4095), L"Resource/Object/Object001.png", ShimiColors::Red)));
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new BreakableObstacle(Point(668, 2346), L"Resource/Object/Object003.png", ShimiColors::Green)));
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new BreakableObstacle(Point(1254, 2335), L"Resource/Object/Object003.png", ShimiColors::Green)));
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new BreakableObstacle(Point(662, 2046), L"Resource/Object/Object003.png", ShimiColors::Green)));
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new BreakableObstacle(Point(1232, 1698), L"Resource/Object/Object003.png", ShimiColors::Green)));
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new BreakableObstacle(Point(2784, 664), L"Resource/Object/Object004.png", ShimiColors::Purple)));
	

	//TriggerBreakableObstacle
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new TriggerBreakableObject(Rect(1921, 3397, 400, 80), L"Boss1Exit")));
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new TriggerBreakableObject(Rect(4362, 1192, 254, 142), L"Boss2Exit")));
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new TriggerBreakableObject(Rect(2532, 5028, 257, 123), L"Boss3Exit")));
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new TriggerBreakableObject(Rect(3894, 3998, 216, 109), L"ToLastBoss")));


	//上辺
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new RectObstacle(Rect(0, -ConfigParam::SIZE_OF_WORLDMARGIN.y, ConfigParam::SIZE_OF_NORMALWORLD.x, ConfigParam::SIZE_OF_WORLDMARGIN.y), RectObstacle::Type::White)));
	//左辺
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new RectObstacle(Rect(-ConfigParam::SIZE_OF_WORLDMARGIN.x, -ConfigParam::SIZE_OF_WORLDMARGIN.y, +ConfigParam::SIZE_OF_WORLDMARGIN.x, ConfigParam::SIZE_OF_NORMALWORLD.y + ConfigParam::SIZE_OF_WORLDMARGIN.y * 2), RectObstacle::Type::White)));
	//下辺
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new RectObstacle(Rect(0, ConfigParam::SIZE_OF_NORMALWORLD.y, ConfigParam::SIZE_OF_NORMALWORLD.x, ConfigParam::SIZE_OF_WORLDMARGIN.y), RectObstacle::Type::White)));
	//右辺
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new RectObstacle(Rect(ConfigParam::SIZE_OF_NORMALWORLD.x, -ConfigParam::SIZE_OF_WORLDMARGIN.y, ConfigParam::SIZE_OF_WORLDMARGIN.x, ConfigParam::SIZE_OF_NORMALWORLD.y + ConfigParam::SIZE_OF_WORLDMARGIN.y * 2), RectObstacle::Type::White)));

	Point BossWorldBasePos = Point(0, ConfigParam::SIZE_OF_NORMALWORLD.y + ConfigParam::SIZE_OF_WORLDMARGIN.y * 2);

	//上辺
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new RectObstacle(Rect(BossWorldBasePos.x, BossWorldBasePos.y - ConfigParam::SIZE_OF_WORLDMARGIN.y, ConfigParam::SIZE_OF_BOSSWORLD.x, ConfigParam::SIZE_OF_WORLDMARGIN.y), RectObstacle::Type::Black)));
	//左辺
	 m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new RectObstacle(Rect(BossWorldBasePos.x - ConfigParam::SIZE_OF_WORLDMARGIN.x, BossWorldBasePos.y - ConfigParam::SIZE_OF_WORLDMARGIN.y, ConfigParam::SIZE_OF_WORLDMARGIN.x, ConfigParam::SIZE_OF_BOSSWORLD.y + ConfigParam::SIZE_OF_WORLDMARGIN.y * 2), RectObstacle::Type::Black)));
	//下辺
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new RectObstacle(Rect(BossWorldBasePos.x,BossWorldBasePos.y + ConfigParam::SIZE_OF_BOSSWORLD.y, ConfigParam::SIZE_OF_BOSSWORLD.x, ConfigParam::SIZE_OF_WORLDMARGIN.y), RectObstacle::Type::Black)));
	//右辺
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new RectObstacle(Rect(BossWorldBasePos.x + ConfigParam::SIZE_OF_BOSSWORLD.x, BossWorldBasePos.y - ConfigParam::SIZE_OF_WORLDMARGIN.y, ConfigParam::SIZE_OF_WORLDMARGIN.x, ConfigParam::SIZE_OF_BOSSWORLD.y + ConfigParam::SIZE_OF_WORLDMARGIN.y * 2), RectObstacle::Type::Black)));


	//Boss
	m_bosses.push_back(std::shared_ptr<Boss>(new Boss1(this, Vec2(1565, 3698))));
	m_bosses.push_back(std::shared_ptr<Boss>(new Boss2(this, Vec2(4156, 306))));
	m_bosses.push_back(std::shared_ptr<Boss>(new Boss3(this, Vec2(4016, 5722))));
	m_bosses.push_back(std::shared_ptr<Boss>(new Boss4(this, BossWorldBasePos + Vec2(750, 500))));

	BGMManager::I()->changeBGM(L"NormalStage");

	m_itemObjects.push_back(Vec2(6480,1590));

	m_savePoint.m_savePoints.push_back(Vec2(1700, 4800));
	m_savePoint.m_savePoints.push_back(Vec2(2924, 1436));
	m_savePoint.m_savePoints.push_back(Vec2(251, 2669));
	m_savePoint.m_savePoints.push_back(Vec2(4818, 2168));
	m_savePoint.m_savePoints.push_back(Vec2(7728, 2457));
	m_savePoint.m_savePoints.push_back(Vec2(5742, 6018));
	m_savePoint.m_savePoints.push_back(Vec2(3981, 3783));


#ifdef _DEBUG
	m_mv.m_life = 5;
	//m_itemObjects.push_back(ItemObject(Vec2(1716, 4544)));
	//m_mv.m_pos = Vec2(750,9000);//ラスボスワープ地点
#endif

}
