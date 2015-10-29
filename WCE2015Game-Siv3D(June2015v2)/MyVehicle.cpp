#include"MyVehicle.hpp"
#include"GameBase.hpp"

#define NO_WALLDEBUG 1

using namespace shimi;

MyVehicle::MyVehicle(GameBase* base) :m_gb(base), m_pos(588, 5864), interval(0), m_shotManager(base), m_state(new state::myvehicle::Normal()), m_isDamaged(false)
{
}

void MyVehicle::collisionPlayerWithObject()
{
	Vec2 futurePos = m_pos + m_v;//そのままならm_v進める

	const int bodySize = 10;

	for (const auto& obstacle : m_gb->m_obstacles)
	{
		for (const s3d::Polygon& wall : obstacle->m_pols)
		{
			const auto& outer = wall.outer();

			//全ての壁のLineについて、wallLinesへ
			for (size_t i = 0; i < outer.size(); ++i)
			{
				const Line line(outer[i], outer[(i + 1) % outer.size()]);

				if ((line.closest(futurePos) - futurePos).length() > 15) continue;

				wallLines.push_back(line);
			}
		}
	}

	//リストを、当たり判定円の中心と交差した壁へのclosestの距離が近い順にならべる
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

	if(!IsNaN(futurePos.x)) m_pos = futurePos;

	wallLines.clear();

}

void MyVehicle::draw()const
{
	const Vec2 myDrawPos = D2Camera::I()->getDrawPos(m_pos);

	const double theta = Circular(m_v).theta;

	TextureAsset(L"Hero").rotate(theta).drawAt(myDrawPos, Alpha(255*m_damageEffect));

	const Vec2  testObjectPos = D2Camera::I()->getDrawPos({ 320, 240 });

	for (auto& s : shotList)
	{
		s->draw(m_pos, m_v);
	}

#ifdef _DEBUG

	
#ifndef NO_WALLDEBUG
	wallDebugDraw();
#endif

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
	m_v.r = Input::KeyA.pressed ? 20.0 : (Input::KeyX.pressed ? 4.0 : 1.8);
#else
	m_v.r = Input::KeyX.pressed ? 4.0 : 1.8;
#endif

	if (Input::KeyZ.pressed && shotable)
	{
		shot();
	}

	if (Input::KeyRight.pressed)
	{
		m_v.theta += 0.08;
	}

	if (Input::KeyLeft.pressed)
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
	//ダメージ受けていなければ処理しない
	if (!m_isDamaged) return;

	changeState(std::shared_ptr<state::myvehicle::MVState>(new state::myvehicle::Damaged()));

	//最後にフラグを戻す
	m_isDamaged = false;
}

MyVehicle::ShotManager::ShotManager(GameBase* gb) :m_gb(gb), m_equipNum(1), m_blankShot(gb)
{
	for (size_t i = 0; i < m_shotPropertys.size(); ++i)
	{
		m_shotPropertys[i].color = static_cast<ShimiColors>(i);
	}

	m_equipShot[0] = std::shared_ptr<Shot>(new WhiteShot(gb));

#ifdef _DEBUG
	m_shotPropertys[static_cast<int>(ShimiColors::Blue)].exp = 50;
	m_shotPropertys[static_cast<int>(ShimiColors::Red)].exp = 50;
	m_shotPropertys[static_cast<int>(ShimiColors::Green)].exp = 50;
	m_shotPropertys[static_cast<int>(ShimiColors::Orange)].exp = 50;
	m_shotPropertys[static_cast<int>(ShimiColors::Purple)].exp = 50;

	m_equipNum = 3;
#endif	

}

void MyVehicle::ShotManager::update()
{
	//上キーが押されたら上の装備、下キーが押されたら下の装備にフォーカスする
	const int add = Input::KeyUp.clicked ? -1 : (Input::KeyDown.clicked ? 1 : 0);

	for (;;)
	{
		m_select = (m_select + m_equipNum + add) % m_equipNum;

		//noneでなければ選択状態に
		if (m_equipShot[m_select]) break;

	}

	//すべての装備のupdate
	for (auto& eq : m_equipShot)
	{
		if (eq)
		{
			eq.value()->update();
		}
	}

	//ショットの成長イベントのupdate
	event();
}

void MyVehicle::ShotManager::event()
{
	for (auto& p : m_shotPropertys)
	{
		if (p.level == 0 && p.exp >= 10)
		{
			//すべての色のレベルが0のとき
			const bool isFirst = AllOf(m_shotPropertys, [](const ShotProperty& sp){ return sp.level == 0; });

			if (isFirst)
			{
				m_equipShot[0] = ShimiColorsToShot(p.color, 1);

				//上がったレベルの色の装備を1番目に自動装備
			}

			//(levelを1に：装備できる色として追加される)
			p.level = 1;

			//レベルアップエフェクト
		}
		else if (p.level == 1 && p.exp >= 80)
		{
			//装備の中に該当の色があれば更新する

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

	//m_equipShotに空でなく、WhiteShotでもないShotがいくつまであるか調べる
	for (i = 0; i < m_equipNum; ++i)
	{
		if (!m_equipShot[i] || !m_equipShot[i].value()->m_color) break;
	}


	std::sort(m_equipShot.begin(), m_equipShot.begin()+i, [](const Optional<std::shared_ptr<Shot>>& a, const Optional<std::shared_ptr<Shot>>& b)
	{
		return ToHierarchy(a.value()->m_color.value()) < ToHierarchy(b.value()->m_color.value());
	});
}
