#include"MyVehicle.hpp"
#include"GameBase.hpp"

#define NO_WALLDEBUG 1

using namespace shimi;

MyVehicle::MyVehicle(GameBase* base) :m_gb(base), interval(0), vehicleType(ShotType::Red), m_shotManager(base)
{
	m_pos = Vec2{850, 850};

}

void MyVehicle::collisionPlayerWithObject()
{
	Vec2 futurePos = m_pos + m_v;//���̂܂܂Ȃ�m_v�i�߂�

	const int bodySize = 10;

	std::vector<Line> wallLines;

	for (const auto& obstacle : m_gb->m_obstacles)
	{
		for (const s3d::Polygon& wall : obstacle.m_pols)
		{
			const auto& outer = wall.outer();

			//�S�Ă̕ǂ�Line�ɂ��āAwallLines��
			for (size_t i = 0; i < outer.size(); ++i)
			{
				const Line line(outer[i], outer[(i + 1) % outer.size()]);

				wallLines.push_back(line);
			}
		}
	}
	//���X�g���A�����蔻��~�̒��S�ƌ��������ǂւ�closest�̋������߂����ɂȂ�ׂ�
	std::sort(wallLines.begin(), wallLines.end(), [&futurePos](const Line& wallA, const Line& wallB)
	{
		return (futurePos - wallA.closest(futurePos)).length() < (futurePos - wallB.closest(futurePos)).length();
	});

	for (int j = 0; j < 2; ++j)
	{
		for (const auto& w : wallLines)
		{
			if (w.intersects(Circle(futurePos, bodySize)))
			{
				const double sink = (bodySize - (futurePos - w.closest(futurePos)).length());

				const Vec2 sinkedDir = (w.closest(futurePos) - futurePos).normalized();

				futurePos -= sinkedDir*sink;

				//Circle(futurePos, 20).drawFrame(2, 0, Palette::Orange);
			}
		}
	}


	m_pos = futurePos;

	if (Input::KeyRight.pressed)
	{
		m_v.theta += 0.08;
	}

	if (Input::KeyLeft.pressed)
	{
		m_v.theta -= 0.08;
	}

}

void MyVehicle::draw()const
{
	for (const auto& o : m_gb->m_obstacles)
	{
		o.draw();
	}
	const Vec2 myDrawPos = D2Camera::I()->getDrawPos(m_pos);

	const double theta = Circular(m_v).theta;

	TextureAsset(L"Hero").rotate(theta).drawAt(myDrawPos);

	const Vec2  testObjectPos = D2Camera::I()->getDrawPos({ 320, 240 });

#ifdef _DEBUG

	FontAsset(L"Debug").draw(Format(m_pos.asPoint()), D2Camera::I()->getDrawPos(m_pos) + Vec2(0, 20), Palette::Black);

#ifndef NO_WALLDEBUG
	wallDebugDraw();
#endif

#endif
}

void MyVehicle::wallDebugDraw()const
{
	for (const auto& o : m_gb->m_obstacles)
	{
		o.drawDebug();
	}

}

void MyVehicle::update()
{
	m_v.r = Input::KeyX.pressed ? 3.0 : 1.8;

	collisionPlayerWithObject();

	for (auto& s : shotList)
	{
		s->update(m_pos, m_v);
	}

	Erase_if(shotList, [=](const std::shared_ptr<ShotGenerator>& sh){ return sh->isDead; });

	if (Input::MouseL.pressed || Input::KeyZ.pressed)
	{
		shot();
	}

	if (const int wh = Mouse::Wheel() != 0)
	{
		vehicleType = static_cast<ShotType>((static_cast<int>(vehicleType)+wh) % (static_cast<int>(ShotType::NumOfType)));
	}

	m_shotManager.update();

	m_shotManager.event();

}


MyVehicle::ShotManager::ShotManager(GameBase* gb) :m_gb(gb)
{
	for (size_t i = 0; i < m_shotPropertys.size(); ++i)
	{
		m_shotPropertys[i].color = static_cast<ShimiColors>(i);
	}

	m_equipShot[0] = std::shared_ptr<Shot>(new WhiteShot(gb));

}


std::shared_ptr<Shot> MyVehicle::ShotManager::ShimiColorsToShot(ShimiColors col, int level)
{
	if (level == 1)
	{
		switch (col)
		{
		case shimi::ShimiColors::Red:
			return std::shared_ptr<Shot>(new RedShot1(m_gb));
			break;
		case shimi::ShimiColors::Orange:
			return std::shared_ptr<Shot>(new RedShot1(m_gb));
			break;
		case shimi::ShimiColors::Green:
			return std::shared_ptr<Shot>(new RedShot1(m_gb));
			break;
		case shimi::ShimiColors::Blue:
			return std::shared_ptr<Shot>(new BlueShot1(m_gb));
			break;
		case shimi::ShimiColors::Purple:
			return std::shared_ptr<Shot>(new RedShot1(m_gb));
			break;
		default:
			assert(false);
			break;
		}
	}
	else if (level==2)
	{
		switch (col)
		{
		case shimi::ShimiColors::Red:
			return std::shared_ptr<Shot>(new RedShot1(m_gb));
			break;
		case shimi::ShimiColors::Orange:
			return std::shared_ptr<Shot>(new RedShot1(m_gb));
			break;
		case shimi::ShimiColors::Green:
			return std::shared_ptr<Shot>(new RedShot1(m_gb));
			break;
		case shimi::ShimiColors::Blue:
			return std::shared_ptr<Shot>(new RedShot1(m_gb));
			break;
		case shimi::ShimiColors::Purple:
			return std::shared_ptr<Shot>(new RedShot1(m_gb));
			break;
		default:
			assert(false);
			break;
		}
	}

	return std::shared_ptr<Shot>(nullptr);
}

void MyVehicle::ShotManager::update()
{
	//��L�[�������ꂽ���̑����A���L�[�������ꂽ�牺�̑����Ƀt�H�[�J�X����
	const int add = Input::KeyUp.clicked ? 1 : (Input::KeyDown.clicked ? -1 : 0);

	for (;;)
	{
		m_select = (m_select + m_equipNum + add) % m_equipNum;

		//none�łȂ���ΑI����Ԃ�
		if (m_equipShot[m_select]) break;

	}

	//���ׂĂ̑�����update
	for (auto& eq : m_equipShot)
	{
		if (eq)
		{
			eq.value()->update();
		}
	}

	//�V���b�g�̐����C�x���g��update
	event();
}

void MyVehicle::ShotManager::event()
{
	for (auto& p : m_shotPropertys)
	{
		if (p.level == 0 && p.exp >= 10)
		{
			//���ׂĂ̐F�̃��x����0�̂Ƃ�
			const bool isFirst = AllOf(m_shotPropertys, [](const ShotProperty& sp){ return sp.level == 0; });

			if (isFirst)
			{
				m_equipShot[0] = ShimiColorsToShot(p.color, 1);
				Println(ToSString(p.color));

				//�オ�������x���̐F�̑�����1�ԖڂɎ�������
			}

			//(level��1�ɁF�����ł���F�Ƃ��Ēǉ������)
			p.level = 1;

			//���x���A�b�v�G�t�F�N�g
		}
		else if (p.level == 1 && p.exp >= 80)
		{
			//�����̒��ɊY���̐F������΍X�V����

		}
	}
}


void MyVehicle::ShotManager::draw()const
{
	for (auto& eq : m_equipShot)
	{
		if (eq)
		{
			eq.value()->draw();
		}
	}

	m_equipShot[m_select].value()->drawFrame();

#ifdef _DEBUG
	FontAsset(L"Debug").draw(L"select:" + Format(m_select) + L" " + Format(m_equipShot[m_select]), Vec2(0, 30));

#endif
}