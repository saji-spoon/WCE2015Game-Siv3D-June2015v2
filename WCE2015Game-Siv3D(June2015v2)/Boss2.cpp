#include"GameBase.hpp"
#include"Camera.hpp"
#include"AwakePlayerAttack.hpp"
#include"Boss4.hpp"
#include"SimpleState.hpp"
#include"Boss3.hpp"

using namespace shimi;

BossUnitBase::BossUnitBase(GameBase* gb, const Vec2& startPos, const Vec2& endPos, const ShimiColors& col, const std::shared_ptr<EnemyShot>& shot)
	:m_gb(gb),
	m_pos(startPos), 
	m_startPos(startPos),
	m_endPos(endPos),
	m_col(col),
	m_shot(shot)
{
	m_flashFrame.m_values.push_back({ 3, 1.0 });
	m_flashFrame.m_values.push_back({ 3, 0.5 });
}

void BossUnitBase::setPath(const Vec2& goal)
{
	m_startPos = m_pos;
	m_endPos = goal;
	m_progress = 0;
}

void BossUnitBase::move(double speed)
{
	m_progress = m_progress + speed;

	const double progressRate = getProgressRate();

	m_pos = EaseInOut(m_startPos, m_endPos, Easing::Cubic, progressRate);
}

void BossUnitBase::draw()const 
{
	Circle(D2Camera::I()->getDrawPos(m_pos), 50).draw(Alpha(200 * m_flashFrame.getData()) * ToColor(m_col));
}

void BossUnitBase::update()
{
	m_flashFrame.update();

	m_shot->update(m_pos, Vec2(-1,0));

	move(3.0);

}


Boss4BabyBase::Boss4BabyBase(GameBase* gb)
	:
	m_gb(gb)
{}

struct Boss4BabyRed : public Boss4BabyBase
{
	std::vector<BossUnitBase> m_units;

	SimpleState m_state;

	Boss4BabyRed()
	{}
	Boss4BabyRed(GameBase* gb, const Vec2& pos)
		:Boss4BabyBase(gb), m_state(50)
	{
		m_units.clear();

		const std::vector<Schedule2> tempSchdl = { { 5.0, 30.0, 3, 150 }, { 5.0, 30.0, 3, 20 }, { 5.0, 30.0, 3, 20 } };

		const std::shared_ptr<EnemyShot> tempShot1(
			new MVAimShot(gb, tempSchdl, BalletAVR(nullptr, L"enemyBallet1", ShimiColors::Red, Vec2(0, 0)), false));
		const std::shared_ptr<EnemyShot> tempShot2(
			new MVAimShot(gb, tempSchdl, BalletAVR(nullptr, L"enemyBallet1", ShimiColors::Red, Vec2(0, 0)), false));

		m_units.push_back(BossUnitBase(gb, pos, pos + Vec2(-497, -222), ShimiColors::Red, tempShot1));
		m_units.push_back(BossUnitBase(gb, pos, pos + Vec2(497, -222), ShimiColors::Red, tempShot2));

	}

	virtual void draw()const override
	{
		for (auto& uni : m_units)
		{
			uni.draw();
		}
	}

	virtual void update()override
	{
		for (auto& uni : m_units)
		{
			uni.update();
		}

		switch (m_state.m_state)
		{
		case 0:
		{
			const bool finish = AllOf(m_units, [](const BossUnitBase& unit){ return unit.m_shot->isFinished(); });
			if (finish)
			{
				m_state.nextState(120);
			}
			break;
		}
		case 1:

			if (m_state.isFinished())
			{
				m_isFinish = true;
			}
			break;
		case 2:
			break;
		default:
			break;
		}


		m_state.update();

	}
};

struct Boss4BabyOrange : public Boss4BabyRed
{
	Boss4BabyOrange()
	{}

	Vec2 m_leftPos;
	Vec2 m_rightPos;

	Boss4BabyOrange(GameBase* gb, const Vec2& pos)
		:Boss4BabyRed(gb, pos)
	{
		m_units.clear();

		std::vector<Schedule1> tempSchdl;

		tempSchdl.push_back({ Vec2(0, Random<double>(3, 6)), 200 });

		for (int i = 0; i < 60; ++i)
		{
			tempSchdl.push_back({ Vec2(0, Random<double>(3,6)), Random<int>(8,15) });
		}

		const std::shared_ptr<EnemyShot> tempShot1(
			new StraightShot(gb, tempSchdl, BalletAVR(nullptr, L"enemyBallet1", ShimiColors::Red, Vec2(0, 0)), false));
		const std::shared_ptr<EnemyShot> tempShot2(
			new StraightShot(gb, tempSchdl, BalletAVR(nullptr, L"enemyBallet1", ShimiColors::Red, Vec2(0, 0)), false));

		m_leftPos = pos + Vec2(-728, -429);
		m_rightPos = pos + Vec2(728, -429);

		m_units.push_back(BossUnitBase(gb, pos, m_leftPos, ShimiColors::Orange, tempShot1));
		m_units.push_back(BossUnitBase(gb, pos, m_rightPos, ShimiColors::Orange, tempShot2));

	}


	virtual void update()override
	{
		for (auto& uni : m_units)
		{
			uni.update();

			//Œ¾‚Á‚½‚è‚«‚½‚è
			if (uni.getProgressRate() == 1.0)
			{
				if (m_leftPos.distanceFrom(uni.m_pos) > m_rightPos.distanceFrom(uni.m_pos))
				{
					uni.setPath(m_leftPos);
				}
				else
				{
					uni.setPath(m_rightPos);
				}
			}
		}


		switch (m_state.m_state)
		{
		case 0:
		{
			const bool finish = AllOf(m_units, [](const BossUnitBase& unit){ return unit.m_shot->isFinished(); });
			if (finish)
			{
				m_state.nextState(120);
			}
			break;
		}
		case 1:

			if (m_state.isFinished())
			{
				m_isFinish = true;
			}
			break;
		case 2:
			break;
		default:
			break;
		}

		m_state.update();
	}
};

struct Boss4BabyGreen : public Boss4BabyRed
{
	Boss4BabyGreen()
	{}

	Boss4BabyGreen(GameBase* gb, const Vec2& pos)
		:Boss4BabyRed(gb, pos)
	{
		m_units.clear();

		std::vector<Schedule2> tempSchdl;

		tempSchdl.push_back({ 9.0, 30.0, 1, 300 });

		for (int i = 0; i < 150; ++i)
		{
			tempSchdl.push_back({ 9.0, 30.0, 1, 5 });
		}

		const std::shared_ptr<EnemyShot> tempShot1(
			new MVAimShot(gb, tempSchdl, BalletAVR(nullptr, L"enemyBallet1", ShimiColors::Red, Vec2(0, 0)), false));
		const std::shared_ptr<EnemyShot> tempShot2(
			new MVAimShot(gb, tempSchdl, BalletAVR(nullptr, L"enemyBallet1", ShimiColors::Red, Vec2(0, 0)), false));
		const std::shared_ptr<EnemyShot> tempShot3(
			new MVAimShot(gb, tempSchdl, BalletAVR(nullptr, L"enemyBallet1", ShimiColors::Red, Vec2(0, 0)), false));

		m_units.push_back(BossUnitBase(gb, pos, pos+Vec2(597, 250), ShimiColors::Green, tempShot1));
		m_units.push_back(BossUnitBase(gb, pos, pos + Vec2(597, 350), ShimiColors::Green, tempShot2));
		m_units.push_back(BossUnitBase(gb, pos, pos + Vec2(597, 450), ShimiColors::Green, tempShot3));
	}
};

struct Boss4BabyBlue : public Boss4BabyRed
{
	Boss4BabyBlue()
	{}

	Boss4BabyBlue(GameBase* gb, const Vec2& pos)
		:Boss4BabyRed(gb, pos)
	{
		m_units.clear();

		std::vector<Schedule1> tempSchdl;

		int y = 30;

		double speed = 4.0;

		double tempos = -728;

		for (;;)
		{
			tempSchdl.push_back({ Vec2(speed, 0.0), 300});

			for (int i = 0; i < 15; ++i)
			{
				tempSchdl.push_back({ Vec2(speed, 0.0), Random<int>(40, 60) });
			}
			const std::shared_ptr<EnemyShot> tempShot(
				new StraightShot(gb, tempSchdl, BalletAVR(nullptr, L"enemyBallet1", ShimiColors::Blue, Vec2(0, 0)), false));

			m_units.push_back(BossUnitBase(gb, pos, pos + Vec2(tempos, -429+y), ShimiColors::Blue, tempShot));

			tempSchdl.clear();

			y += Random(70, 140);

			if (y > ConfigParam::SIZE_OF_BOSSWORLD.y)break;

			speed *= -1;
			tempos *= -1;

		}
	}
};

struct Boss4BabyPurple : public Boss4BabyRed
{
	Boss4BabyPurple()
	{}

	Boss4BabyPurple(GameBase* gb, const Vec2& pos)
		:Boss4BabyRed(gb, pos)
	{
		m_units.clear();

		std::vector<Schedule2> tempSchdl;

		int i = 0;

		tempSchdl.push_back({ 4.0, 20 + 280.0 - (280.0 / 10.0) * i, 6, 200 });

		for (int i = 1; i < 10; ++i)
		{
			tempSchdl.push_back({ 4.0, 20 + 280.0 - (280.0 / 10.0) * i, 6, 70});

		}

		const std::shared_ptr<EnemyShot> tempShot1(
			new MVAimShot(gb, tempSchdl, BalletAVR(nullptr, L"enemyBallet1", ShimiColors::Purple, Vec2(0, 0)), false));

		const std::shared_ptr<EnemyShot> tempShot2(
			new MVAimShot(gb, tempSchdl, BalletAVR(nullptr, L"enemyBallet1", ShimiColors::Purple, Vec2(0, 0)), false));

		m_units.push_back(BossUnitBase(gb, pos, pos + Vec2(-696, 0), ShimiColors::Purple, tempShot1));
		m_units.push_back(BossUnitBase(gb, pos, pos + Vec2(696, 0), ShimiColors::Purple, tempShot2));

	}

};



Boss4::Boss4(GameBase* gb, const Vec2& pos, const std::shared_ptr<state::boss4::Boss4Base>& state)
	:Boss(gb, pos),
	m_state(state),
	m_weekPs(5),
	m_bossArea(0, ConfigParam::SIZE_OF_NORMALWORLD.y + ConfigParam::SIZE_OF_WORLDMARGIN.y * 2, ConfigParam::SIZE_OF_BOSSWORLD)
{
	m_weekPs[0] = Vec2(-252, 77);
	m_weekPs[1] = Vec2(-37, -225);
	m_weekPs[2] = Vec2(-209, -133);
	m_weekPs[3] = Vec2(-98, 211);
	m_weekPs[4] = Vec2(193, -167);

#ifdef _DEBUG
	m_life = 0;
#endif

}


void Boss4::draw()const
{
	m_anime.draw(D2Camera::I()->getDrawPos(m_pos), m_theta);

	//if (m_barrier) drawBarrier();

	if (m_baby)	m_baby->draw();

#ifdef _DEBUG
	for (int i = 0; i < m_weekPs.size(); ++i)
	{
		const ShimiColors col = static_cast<ShimiColors>(i);

		Circle(getWeekPos(col), 50).movedBy(D2Camera::I()->getDrawPos(Vec2(0, 0))).draw(ToColor(col));
	}
#endif
	
}

void Boss4::update()
{
	m_state->execute(*this);

	if (m_baby)	m_baby->update();

	if (m_isDead) return;

	AwakeEnemyAttack(m_gb, getMyCollision(m_pos), ShimiColors::Red, 1);
}

void Boss4::debugDraw()const
{
#ifdef _DEBUG
	m_bossArea.movedBy(D2Camera::I()->getDrawPos(Vec2(0, 0)).asPoint()).drawFrame(5.0, 0.0, Alpha(128) * Palette::Red);
#endif

}

bool Boss4::isInBossBattle()const
{
	return m_bossArea.intersects(Circle(m_gb->getMyVehiclePos(), 10));
}

void Boss4::popBaby(const ShimiColors& col)
{
	switch (col)
	{
	case shimi::ShimiColors::Red:
		m_baby = std::shared_ptr<Boss4BabyBase>(new Boss4BabyRed(m_gb, m_pos));
		break;
	case shimi::ShimiColors::Orange:
		m_baby = std::shared_ptr<Boss4BabyBase>(new Boss4BabyOrange(m_gb, m_pos));
		break;
	case shimi::ShimiColors::Green:
		m_baby = std::shared_ptr<Boss4BabyBase>(new Boss4BabyGreen(m_gb, m_pos));
		break;
	case shimi::ShimiColors::Blue:
		m_baby = std::shared_ptr<Boss4BabyBase>(new Boss4BabyBlue(m_gb, m_pos));
		break;
	case shimi::ShimiColors::Purple:
		m_baby = std::shared_ptr<Boss4BabyBase>(new Boss4BabyPurple(m_gb, m_pos));
		break;
	case shimi::ShimiColors::ColorNum:
		m_baby = std::shared_ptr<Boss4BabyBase>(new Boss4BabyPurple(m_gb, m_pos));
		break;
	default:
		break;
	}
}

Vec2 Boss4::getWeekPos(const ShimiColors& col)const
{
	const int index = static_cast<int>(col);

	return m_pos + m_weekPs[index].rotated(m_theta);
}

void Boss4::killedSilent()
{
	m_damagable = false;

	m_isDead = true;

	m_anime.m_mode = Boss4AnimeMode::Vanished;
}

Boss3::Boss3(GameBase* gb, const Vec2& pos, std::shared_ptr<state::boss3::Boss3Base> state) :Boss(gb, pos), m_state(state)
{

	m_bossArea = Obstacle(Point(3510, 5232), L"Resource/Object/boss3_area.png", 12.0);
#ifdef _DEBUG
	m_life = 0;
	m_state = std::shared_ptr<state::boss3::Boss3Base>(new state::boss3::Damagable());
#endif
}

void Boss3::draw()const
{
	m_anime.draw(D2Camera::I()->getDrawPos(m_pos), 0);

	if (m_barrier) drawBarrier();


}

void Boss3::update()
{
	m_state->execute(*this);

	if (m_isDead) return;

	AwakeEnemyAttack(m_gb, getMyCollision(m_pos), ShimiColors::Blue, 1);
}

void Boss3::debugDraw()const
{
#ifdef _DEBUG
	m_bossArea.m_pols.drawFrame(D2Camera::I()->getDrawPos(Vec2(0, 0)), 3.0, Alpha(128) * Palette::Red);
#endif

}

bool Boss3::isInBossBattle()const
{
	return m_bossArea.m_pols.intersects(Circle(m_gb->getMyVehiclePos(), 10));
}

void Boss3::drawBarrier()const
{
	Circle(D2Camera::I()->getDrawPos(m_pos), 200).drawFrame(0, 5.0, ToColor(ShimiColors::Blue));
	Circle(D2Camera::I()->getDrawPos(m_pos), 200).draw(Alpha(80) * ToColor(ShimiColors::Blue));
}

void Boss3::killedSilent()
{
	m_damagable = false;

	m_isDead = true;

	m_anime.m_mode = Boss3AnimeMode::Vanished;
}
