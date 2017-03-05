#include"MyVehicle.hpp"
#include"GameBase.hpp"
#include"Config.hpp"
#include"MyVehicleSave.hpp"

using namespace shimi;

MyVehicle::MyVehicle(GameBase* base) :
        m_gb(base), 
        m_pos(588, 5864),
        interval(0),
        m_shotManager(base),
        m_state(new state::myvehicle::Normal()), m_isDamaged(false)
{
}

void MyVehicle::collisionPlayerWithObject()
{
	Vec2 futurePos = m_pos + m_v;//���̂܂܂Ȃ�m_v�i�߂�
	const int bodySize = 10;

	for (const auto& obstacle : m_gb->m_obstacles)
	{
		for (const s3d::Polygon& wall : obstacle->m_pols)
		{
			const auto& outer = wall.outer();

			//�S�Ă̕ǂ�Line�ɂ��āAwallLines��
			for (size_t i = 0; i < outer.size(); ++i)
			{
				const Line line(outer[i], outer[(i + 1) % outer.size()]);

				if ((line.closest(futurePos) - futurePos).length() > 15) continue;

				wallLines.push_back(line);
			}
		}
	}

	//���X�g���A�����蔻��~�̒��S�ƌ��������ǂւ�closest�̋������߂����ɂȂ�ׂ�
	std::sort(wallLines.begin(), wallLines.end(), [&futurePos](const Line& wallA, const Line& wallB)
	{
		return (futurePos - wallA.closest(futurePos)).length() <
			(futurePos - wallB.closest(futurePos)).length();
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

	if(!IsNaN(futurePos.x)) m_pos = futurePos;

	wallLines.clear();

}

void MyVehicle::draw()const
{
	if (!m_drawable) return;

	const Vec2 myDrawPos = D2Camera::I()->getDrawPos(m_pos);

	const double theta = Circular(m_v).theta;

	if (m_life >= 3)
	{
		TextureAsset(L"Hero").rotate(theta).drawAt(myDrawPos, Alpha(TOUINT(255 * m_damageEffect)));
	}
	else if (m_life == 2)
	{
		TextureAsset(L"HeroX").rotate(theta).drawAt(myDrawPos, Alpha(TOUINT(255 * m_damageEffect)));
	}
	else if (m_life == 1)
	{
		TextureAsset(L"HeroXX").rotate(theta).drawAt(myDrawPos, Alpha(TOUINT(255 * m_damageEffect)));
	}
	else 
	{
		TextureAsset(L"HeroXXX").rotate(theta).drawAt(myDrawPos, Alpha(TOUINT( 255 * m_damageEffect)));
	}


	for (auto& s : shotList)
	{
		s->draw(m_pos, m_v);
	}

#ifdef _DEBUG
#endif
}

void MyVehicle::wallDebugDraw()const
{
	for (const auto& o : m_gb->m_obstacles)
	{
		o->drawDebug();
	}

}

void MyVehicle::update()
{
	m_state->execute(*this);

}

void MyVehicle::controll(bool shotable)
{
#ifdef _DEBUG
	m_v.r = Input::KeyA.pressed ? 20.0 : (ConfigParam::KEY_B_PRESSED() ? 4.0 : 1.8);
#else
	m_v.r = ConfigParam::KEY_B_PRESSED() ? 4.0 : 1.8;
#endif

	if (ConfigParam::KEY_A_PRESSED() && shotable)
	{
		shot();
	}

	if (ConfigParam::KEY_RIGHT_PRESSED())
	{
		m_v.theta += 0.08;
	}

	if (ConfigParam::KEY_LEFT_PRESSED())
	{
		m_v.theta -= 0.08;
	}

}

void MyVehicle::GameUpdate(bool damagable, bool shotable)
{
	m_isDamaged = m_isDamaged && damagable;

	controll(shotable);

	collisionPlayerWithObject();

	shotListUpdate();

	damageUpdate();

	m_shotManager.update();

	m_shotManager.event();
}

void MyVehicle::damageUpdate()
{
	//�_���[�W�󂯂Ă��Ȃ���Ώ������Ȃ�
	if (!m_isDamaged) return;

	if (m_life <= 0)
	{
		changeState(std::shared_ptr<state::myvehicle::MVState>(new state::myvehicle::Killed()));
	}
	else
	{
		changeState(std::shared_ptr<state::myvehicle::MVState>(new state::myvehicle::Damaged()));
		--m_life;
	}
	//�Ō�Ƀt���O��߂�
	m_isDamaged = false;
}

void MyVehicle::recoverPos()
{
	m_pos = m_gb->m_savePoint.getRecoverPoint();
	m_v = Circular(3.0, 0);
}

void MyVehicle::reset()
{
	m_shotManager.resetEquipShot();
	m_life = 3;

	shotList.clear();
	m_isDamaged = false;

}

MyVehicleSave MyVehicle::getSave()const
{
	MyVehicleSave mvs;

	mvs.m_mvPos = m_pos;
	mvs.m_equipNum = m_shotManager.m_equipNum;
	mvs.m_shotPropertys = m_shotManager.m_shotPropertys;
	for (auto& sh : m_shotManager.m_equipShot)
	{
		if (!sh)
		{
			mvs.m_equipShot.push_back(none);
		}
		else
		{
			mvs.m_equipShot.push_back(MyVehicleSave::ShotBox{sh.value()->m_color});
		}
	}

	return mvs;

}

//�����œn���ꂽ�Z�[�u�̏���ǂ݂���
bool MyVehicle::load(const MyVehicleSave& mvs)
{
	m_pos = mvs.m_mvPos;
	m_shotManager.m_equipNum = mvs.m_equipNum;
	m_shotManager.m_shotPropertys = mvs.m_shotPropertys;

	assert(mvs.m_equipShot.size()==3);

	for (size_t i = 0; i < mvs.m_equipShot.size(); ++i)
	{
		if (const auto& shotExist = mvs.m_equipShot[i])
		{
			if (const auto& colorExist = shotExist.value().m_color)
			{
				m_shotManager.m_equipShot[i] = m_shotManager.ShimiColorsToShot(colorExist.value());
			}
			else
			{
				m_shotManager.m_equipShot[i] = m_shotManager.getWhiteShotPtr();
			}

		}
		else
		{
			m_shotManager.m_equipShot[i] = none;
		}
	}

	return true;
}

MyVehicle::ShotManager::ShotManager(GameBase* gb) :m_gb(gb), m_equipNum(1)
{
	for (size_t i = 0; i < m_shotPropertys.size(); ++i)
	{
		m_shotPropertys[i].color = static_cast<ShimiColors>(i);
	}

	m_equipShot[0] = getWhiteShotPtr();

#ifdef _DEBUG
	m_shotPropertys[static_cast<int>(ShimiColors::Blue)].exp = 9;
	m_shotPropertys[static_cast<int>(ShimiColors::Red)].exp = 9;
	m_shotPropertys[static_cast<int>(ShimiColors::Green)].exp = 9;
	m_shotPropertys[static_cast<int>(ShimiColors::Orange)].exp = 9;
	m_shotPropertys[static_cast<int>(ShimiColors::Purple)].exp = 9;

	m_equipNum = 1;
#endif	

}

void MyVehicle::ShotManager::update()
{
	//��L�[�������ꂽ���̑����A���L�[�������ꂽ�牺�̑����Ƀt�H�[�J�X����
	const int add = ConfigParam::KEY_DOWN_CLICKED() ? 1 : (ConfigParam::KEY_UP_CLICKED() ? -1 : 0);

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

				//�オ�������x���̐F�̑�����1�ԖڂɎ�������
			}

			//(level��1�ɁF�����ł���F�Ƃ��Ēǉ������)
			p.level = 1;

			const NotifyStr2 notify(ToSString(p.color) + L"Shot", L"Get!:", Palette::White, 120, ToColor(p.color));
			EffectManager::I()->effect.add<Notify>(m_gb, notify);
		}
		else if (p.level == 1 && p.exp >= 200)
		{
			//�����̒��ɊY���̐F������΍X�V����

		}
	}
}

void MyVehicle::ShotManager::draw(const Vec2& pos, const Vec2& v)const
{
	for (auto& eq : m_equipShot)
	{
		if (eq)
		{
			eq.value()->draw(pos, v);
		}
	}

	m_equipShot[m_select].value()->drawFrame(pos, v);

#ifdef _DEBUG
	FontAsset(L"Debug").draw(L"select:" + Format(m_select) + L" " + Format(m_equipShot[m_select]), Vec2(0, 30), Palette::Black);

#endif
}

void MyVehicle::ShotManager::drawAsPreview(const Vec2& pos, const Vec2& v)const
{
	for (auto& eq : m_equipShot)
	{
		if (eq)
		{
			eq.value()->draw(pos, v);
		}
	}
}

void MyVehicle::ShotManager::shot(const Vec2& pos, const Vec2& v)
{
	m_equipShot[m_select].value()->shot(pos, v);
}

std::shared_ptr<Shot> MyVehicle::ShotManager::ShimiColorsToShot(const ShimiColors& col, int level)
{
	if (level == 1)
	{
		switch (col)
		{
		case shimi::ShimiColors::Red:
			return std::shared_ptr<Shot>(new RedShot1(m_gb));
			break;
		case shimi::ShimiColors::Orange:
			return std::shared_ptr<Shot>(new OrangeShot1(m_gb));
			break;
		case shimi::ShimiColors::Green:
			return std::shared_ptr<Shot>(new GreenShot1(m_gb));
			break;
		case shimi::ShimiColors::Blue:
			return std::shared_ptr<Shot>(new BlueShot1(m_gb));
			break;
		case shimi::ShimiColors::Purple:
			return std::shared_ptr<Shot>(new PurpleShot1(m_gb));
			break;
		default:
			assert(false);
			break;
		}
	}
	else if (level == 2)
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

std::shared_ptr<Shot> MyVehicle::ShotManager::ShimiColorsToShot(const ShimiColors& col)
{
	return ShimiColorsToShot(col, getLevel(col));
}

int MyVehicle::ShotManager::getLevel(const ShimiColors& col)
{
	int index = static_cast<int>(col);

	return m_shotPropertys[index].level;
}

bool MyVehicle::ShotManager::isAlreadyEquiped(const ShimiColors& col)
{

	
	auto it = std::find_if(m_equipShot.begin(), m_equipShot.end(), [&col](const Optional<std::shared_ptr<Shot>>& c)
	{
#ifdef _DEBUG
		if (!c)
		{
			LOG_DEBUG(L"isAlreadyEquiped : blank shot");
		}
		else
		{
			LOG_DEBUG(L"isAlreadyEquiped : " + ToSString(c.value()->m_color.value()) + L"==" + ToSString(col));
		}
#endif

		if (!c)
		{
			return false;
		} 
		else
		{
			return c.value()->m_color && c.value()->m_color.value() == col;
		}
	});
	

	return it != m_equipShot.end();
}

void MyVehicle::ShotManager::sortEquipShotWithHierarchy()
{
	int i;

	//m_equipShot�ɋ�łȂ��AWhiteShot�ł��Ȃ�Shot�������܂ł��邩���ׂ�
	for (i = 0; i < m_equipNum; ++i)
	{
		if (!m_equipShot[i] || !m_equipShot[i].value()->m_color) break;
	}


	std::sort(m_equipShot.begin(), m_equipShot.begin()+i, [](const Optional<std::shared_ptr<Shot>>& a, const Optional<std::shared_ptr<Shot>>& b)
	{
		return ToHierarchy(a.value()->m_color.value()) < ToHierarchy(b.value()->m_color.value());
	});
}

void  MyVehicle::ShotManager::resetEquipShot()
{
	for (auto& tempShot : m_equipShot)
	{
		//���V���b�g�ł͂Ȃ�����������Ă���Ƃ��A���j���[���J���ۂɃC���X�^���X��蒼���i�΂̃`���[�W�Ȃǂ������j
		if (tempShot && tempShot.value()->m_color)
		{
			const ShimiColors targetColor = tempShot.value()->m_color.value();
			const int level = getLevel(targetColor);
			tempShot = ShimiColorsToShot(targetColor, level);
		}
	}
}

void MyVehicle::warp()
{
	changeState(std::shared_ptr<state::myvehicle::MVState>(new state::myvehicle::ToBoss()));
}

void MyVehicle::addSlot()
{
	++m_shotManager.m_equipNum;

	assert(m_shotManager.m_equipNum <= 3);
}
