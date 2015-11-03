#include"GameBase.hpp"
#include"EnemyShot.hpp"
#include"BGMManager.hpp"
#include"Boss2.hpp"
using namespace shimi;

void shimi::GameBase::init()
{
	readEnemyData(L"Resource/Data/test3.csv");
	
	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new Obstacle({ 0, 0 }, L"Resource/Stage/stage_beehive.png", 12.0)));

	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new Obstacle({ 62, 3176 }, L"Resource/Stage/stage_start.png", 12.0)));
	
	//m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new Obstacle(Point{ 1757, 0 }*2, L"Resource/Stage/stage_planet.png", 12.0)));
	//m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new Obstacle(Point{ 1311, 1454 }*2, L"Resource/Stage/stage_crystal.png", 12.0)));
	//m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new Obstacle(Point{ 1002, 1551 }*2, L"Resource/Stage/stage_fish_and_vine.png", 12.0)));
	

	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new BreakableObstacle(Rect(972, 4095, 50, 200), ShimiColors::Red)));

	m_obstacles.push_back(std::shared_ptr<ObstacleBase>(new TriggerBreakableObject(Rect(1921, 3397, 400, 80), L"Boss1Exit")));

	//m_bosses.push_back(std::shared_ptr<Boss>(new Boss1(this, Vec2(1565, 3698))));
	
	m_bosses.push_back(std::shared_ptr<Boss>(new Boss2(this, Vec2(4156, 306))));

	BGMManager::I()->changeBGM(L"NormalStage");

	m_EM.popForce(getMyVehiclePos(), ConfigParam::POP_DISTANCE_IN);

#ifdef _DEBUG
	//m_mv.m_pos = Vec2(3700,875);
#endif

}
