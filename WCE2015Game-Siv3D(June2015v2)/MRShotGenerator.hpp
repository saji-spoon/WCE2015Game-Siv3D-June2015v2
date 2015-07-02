#include<Siv3D.hpp>
#include"MRBallet.hpp"

class MRShotGenerator
{
public:

	MRShotGenerator();

	MRShotGenerator(unsigned int dl) :isDead(false), deadLine(dl)
	{}

	void start(){ timer.restart(); }

	virtual void generate(const Point& vehiclePos) = 0;

	void update(const Point& vehiclePos)
	{
		if (isDead) return;

		if (timer.elapsed() > deadLine)
		{
			isDead = true;
			return;
		}

		generate(vehiclePos);
	}

	bool isDead;//削除して良い状態かどうか

protected:
	TimerMillisec timer;//処理の時間の終わり管理用

	unsigned int deadLine;//終わりの時間


};

class MRShotRound : public MRShotGenerator
{
public:

	MRShotRound(){}

	MRShotRound(unsigned int dl, Point p) :MRShotGenerator(dl), pos(p)
	{
		wait.start();
	}

	void generate(const Point& vehiclePos)override
	{
		if (wait.elapsed() > 10)
		{
			for (int i = 0; i < 4; ++i)
			{
				MREntityManager::GetInstance()->createBallet(std::shared_ptr<MRBallet>(new MRBalletAVR(
					Point(pos.x, 240),
					L"ballet1",
					0.23,
					(7.0 / 640.0*pos.x + (20.0*i) / 360) * 2 * Pi,
					0.2,
					0.08)));
			}
			/*
			MREntityManager::GetInstance()->createBallet(std::shared_ptr<MRBallet>(new MRBalletAVR(
				Point(pos.x, 240),
				L"mame",
				0.23,
				(7.0 / 640.0*pos.x + 270.0 / 360) * 2 * Pi,
				0.2,
				0.08)));
			MREntityManager::GetInstance()->createBallet(std::shared_ptr<MRBallet>(new MRBalletAVR(
				Point(pos.x, 240),
				L"mame",
				0.23,
				(7.0 / 640.0*pos.x + 90.0 / 360) * 2 * Pi,
				0.2,
				0.08)));
			MREntityManager::GetInstance()->createBallet(std::shared_ptr<MRBallet>(new MRBalletAVR(
				Point(pos.x, 240),
				L"mame",
				0.23,
				(7.0 / 640.0*pos.x + 180.0 / 360) * 2 * Pi,
				0.2,
				0.08)));
			MREntityManager::GetInstance()->createBallet(std::shared_ptr<MRBallet>(new MRBalletAVR(
				Point(pos.x, 240),
				L"mame",
				0.23,
				(7.0 / 640.0*pos.x + 360.0 / 360) * 2 * Pi,
				0.2,
				0.08)));
				*/
			wait.restart();
		}
	}
private:
	TimerMillisec wait;

	Point pos;//発射基準点
};

class MRShotSakura : public MRShotGenerator
{
public:

	MRShotSakura(){}

	MRShotSakura(unsigned int dl) :MRShotGenerator(dl)
	{
		wait.start();
	}

	void generate(const Point& vehiclePos)override
	{
		if (wait.elapsed() > 10)
		{
			for (int i = 0; i < 5; ++i)
			{
				MREntityManager::GetInstance()->createBallet(std::shared_ptr<MRBallet>(new MRBalletAVR(
					vehiclePos,
					L"ballet3",
					0.23,
					(7.0 / 640.0*vehiclePos.x + 0.2*i) * 2 * Pi,
					0.2,
					0.08)));
			}

		
			wait.restart();
		}
	}
private:
	TimerMillisec wait;
};

class MRShotChase : public MRShotGenerator
{
public:

	MRShotChase(){}

	MRShotChase(unsigned int dl) :MRShotGenerator(dl)
	{
		wait.start();
	}

	void generate(const Point& vehiclePos)override
	{
		const Point target = MREntityManager::GetInstance()->getChasedEnemyPoint();

		for (int i = 0; i < 20; ++i)
		{
			const Vec2 balletPos = Circular0(60, 0.05 * i * 2 * Pi) + vehiclePos;

			MREntityManager::GetInstance()->createBallet(std::shared_ptr<MRBallet>(new MRBalletAVR(
				balletPos.asPoint(),
				L"ballet2",
				3.0,
				Circular(target - balletPos).theta - Pi / 2.0,
				0)));
		}

		for (int i = 0; i < 40; ++i)
		{
			const Vec2 balletPos = Circular0(90, 0.025 * i * 2 * Pi) + vehiclePos;

			MREntityManager::GetInstance()->createBallet(std::shared_ptr<MRBallet>(new MRBalletAVR(
				balletPos.asPoint(),
				L"ballet2",
				3.0,
				Circular(target - balletPos).theta - Pi / 2.0,
				0)));
		}
	}
private:
	TimerMillisec wait;
};
