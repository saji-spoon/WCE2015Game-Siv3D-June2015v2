#include"Shot.hpp"
#include"GameBase.hpp"
#include"AwakePlayerAttack.hpp"
#include"ShotGenerator.hpp"

using namespace shimi;

//���́F���@�̈ʒu�A���@�̌����A���@�����������Ă���Ƃ��̈ʒu�@�o�́F�w�肳�ꂽ���@�̈ʒu�A���@�̌����ł̈ʒu
Vec2 getPosFromRelativeLocationFromMV(const Vec2& mvPos, const Vec2& mvV, const Vec2& relPos)
{
	const double theta = Circular(mvV).theta;

	const Vec2 posD = mvPos + relPos.rotated(theta);

	return posD;
}

//���́F���@�����������Ă���Ƃ��̈ʒu�@�o�́Fgb.m_mv�̈ʒu�E���x�ł̈ʒu
Vec2 getPosFromRelativeLocationFromMV(GameBase* gb, const Vec2& relPos)
{
	return getPosFromRelativeLocationFromMV(gb->getMyVehiclePos(), gb->getMyVehicleV(), relPos);
}

//�����摜tex���ʒupos, ����v�̎��@�̎���ɁA�p�[�c��`��
//rotPos�c�摜���ł̉�]�̎x�_�ƂȂ���W relPos�c���@���S����rotPos�܂ł̑��Έʒu isMirror�c�������̂����E�Ώ̂ɕ`�悷�邩�ǂ���
void DrawTexAsShot(const Vec2& vPos, const Vec2& v, const Texture& tex, const Vec2& rotPos, const Vec2 relPos, bool isMirror)
{
	const Vec2 pos = D2Camera::I()->getDrawPos(vPos);

	//��]�x�_
	const Vec2 rotPosMir = Vec2{ (tex.size.x - rotPos.x), rotPos.y };
	//��]
	const double theta = Circular(v).theta;

	const Vec2 posD = pos + relPos.rotated(theta) - rotPos;
	tex.rotateAt(rotPos, theta).draw(posD);

	if (!isMirror) return;

	const Vec2 posDmir = pos + Vec2(-relPos.x, relPos.y).rotated(theta) - rotPosMir;
	tex.mirror().rotateAt(rotPosMir, theta).draw(posDmir);
}


void RedShot1::draw(const Vec2& pos, const Vec2& v)const
{
	DrawTexAsShot(pos, v, m_tex, Vec2(201,258), Vec2(20, 0), true);
	/*
	//��]�x�_
	const Vec2 rotPos = Vec2(0, 50);
	const Vec2 rotPosMir = Vec2{ (m_tex.size.x - rotPos.x), rotPos.y };
	//���@���S����̂���
	const Vec2 relPos = Vec2(20, 0);
	//��]
	const double theta = Circular(v).theta;

	const Vec2 posD = pos + relPos.rotated(theta) - rotPos;
	m_tex.rotateAt(rotPos, theta).draw(posD);
	const Vec2 posDmir = pos + (-relPos).rotated(theta) - rotPosMir;
	m_tex.mirror().rotateAt(rotPosMir, theta).draw(posDmir);
	*/
}

void RedShot1::drawFrame(const Vec2& pos, const Vec2& v)const
{
	DrawTexAsShot(pos, v, m_frameTex, Vec2(201, 258), Vec2(20, 0), true);

	/*
	//�V���b�g�I�����̃t���[���`��
	const Vec2 relPos = Vec2(0, -40);
	const double theta = Circular(v).theta;

	const Vec2 posD = pos + relPos.rotated(theta);
	Circle(posD, 10).drawFrame(4.0, 0.0, Color(224, 0, 0, 128));
	*/
}

void RedShot1::shot(const Vec2& pos, const Vec2& v)
{
	if (m_count > 0) return;

	for (int i = 0; i < 3; ++i)
	{
		m_gb->m_myBM.m_ballets.push_back(std::shared_ptr<Ballet>(new BalletAVR(
			&(m_gb->m_myBM),
			L"redBallet",
			m_color.value(),
			m_gb->getMyVehiclePos(),
			5.00,
			Circular3(m_gb->m_mv.m_v).theta + (i - 1) * Pi / 36.0,
			0.0,
			0.0,
			ScheduleTimer({ 30, 80 }))));
	}

	SoundAsset(L"MyBallet").playMulti();

	m_count = m_interval;
}


void BlueShot1::draw(const Vec2& pos, const Vec2& v)const
{
	DrawTexAsShot(pos, v, m_tex, Vec2(250, 201), Vec2(0, 50), false);
}

void BlueShot1::drawFrame(const Vec2& pos, const Vec2& v)const
{
	DrawTexAsShot(pos, v, m_frameTex, Vec2(250, 201), Vec2(0, 50), false);
}

void BlueShot1::shot(const Vec2& pos, const Vec2& v)
{
	if (m_count > 0) return;

	m_gb->m_mv.shotList.push_back(std::shared_ptr<ShotGenerator>( new BlueShot1Generator(m_gb,300, getPosFromRelativeLocationFromMV(pos, v, Vec2(0,120)))));


	/*
	for (int i = 0; i < 3; ++i)
	{
		m_gb->m_myBM.m_ballets.push_back(std::shared_ptr<Ballet>(new BalletAVR(
			&(m_gb->m_myBM),
			L"ballet3",
			m_gb->getMyVehiclePos(),
			5.00,
			Circular3(m_gb->m_mv.m_v).theta + (i - 1) * Pi / 36.0,
			0.0,
			0.0)));
	}
	*/

	m_count = m_interval;
}


GreenShot1::GreenShot1(GameBase* gb) :Shot(gb, 70, ShimiColors::Green)
{}

void GreenShot1::draw(const Vec2& pos, const Vec2& v)const
{
	DrawTexAsShot(pos, v, m_tex, Vec2(250, 282), Vec2(0, -28), false);

	switch (m_state)
	{
	case 0:
		break;
	case 1:
		//�`���[�W�G�t�F�N�g
		Circle(D2Camera::I()->getDrawPos(getPosFromRelativeLocationFromMV(m_gb, Vec2(0, -28))), 30 * (1.0 - 1.0 * m_stateTimer / ConfigParam::TIME_GREENCHARGE)).drawFrame(2.0, 0.0, ToColor(ShimiColors::Green).setAlpha(130));

		break;
	case 2:
	{
		const Point DrawPos = D2Camera::I()->getDrawPos(m_beam.begin.asPoint()).asPoint();

		//���[�U�[�`��
		Rect(DrawPos - Point(10, 0), { 20, m_beam.length() }).rotatedAt(DrawPos, Circular6(m_beam.vector()).theta).draw(ToColor(ShimiColors::Green));
	}
		//0�֖߂�
	default:
		break;
	}
}

void GreenShot1::drawFrame(const Vec2& pos, const Vec2& v)const
{
	DrawTexAsShot(pos, v, m_frameTex, Vec2(250, 282), Vec2(0, -28), false);
}

void GreenShot1::shot(const Vec2& pos, const Vec2& v)
{
	if (m_state != 0) return;
	


	m_count = m_interval;
	m_state = 1;
}

void GreenShot1::update() 
{
	if (m_count > 0) --m_count; 

	switch(m_state)
	{
	case 0:	
		//�����Ȃ���ԁF0��1��shot�őJ�ڂ���
		break;
	case 1:
		//�`���[�W��
		if (m_stateTimer >= ConfigParam::TIME_GREENCHARGE)
		{
			changeState(2);

			beamUpdate();

			return;
		}

		++m_stateTimer;

		break;
	case 2:
	{
		//���˒�
		if (m_stateTimer >= ConfigParam::TIME_GREENBURST)
		{
			changeState(0);

			return;
		}

		++m_stateTimer;

		beamCollision();

		beamUpdate();
	}

	default:
		break;
	}



};

void GreenShot1::beamUpdate()
{
	const Vec2 pos = m_gb->getMyVehiclePos();
	const Vec2 v = m_gb->getMyVehicleV();

	m_beam = Line(pos, pos + v.normalized() * 400);

	for (const auto& walls : m_gb->m_obstacles)
	{
		for (const auto& wall : walls->m_pols)
		{
			const auto& outer = wall.outer();

			for (size_t i = 0; i < outer.size(); ++i)
			{
				const Line line(outer[i], outer[(i + 1) % outer.size()]);

				const auto& cross = line.intersectsAt(m_beam);

				if (cross && m_beam.begin.distanceFrom(cross.value()) < m_beam.begin.distanceFrom(m_beam.end))
				{
					m_beam.end = cross.value();
				}
			}
		}
	}
}

void GreenShot1::beamCollision()
{
	const Vec2 pos = m_gb->getMyVehiclePos();
	const Vec2 v = m_gb->getMyVehicleV();

	const auto& colRect = Rect(pos.asPoint() - Point(10, 0), Point( 20, m_beam.length() )).rotatedAt(pos, Circular6(m_beam.vector()).theta);

	AwakePlayerAttack(m_gb, colRect, m_color.value(), 3);

}

OrangeShot1::OrangeShot1(GameBase* gb):Shot(gb, 60, ShimiColors::Orange)
{}

void OrangeShot1::draw(const Vec2& pos, const Vec2& v)const
{
	DrawTexAsShot(pos, v, m_tex, Vec2(216, 241), Vec2(30, 60), true);
}

void OrangeShot1::drawFrame(const Vec2& pos, const Vec2& v)const
{
	DrawTexAsShot(pos, v, m_frameTex, Vec2(216, 241), Vec2(30, 60), true);
}

void OrangeShot1::shot(const Vec2& pos, const Vec2& v)
{
	if (m_count > 0) return;

	const Vec2 burstPos1 = getPosFromRelativeLocationFromMV(m_gb, Vec2(57, 102));

	const Vec2 burstPos2 = getPosFromRelativeLocationFromMV(m_gb, Vec2(-57, 102));

	const auto& c = m_gb->getNearestEnemyPos();

	const Vec2 targetPos = c ? c.value() : (getPosFromRelativeLocationFromMV(m_gb, Vec2(0, -120)));

	m_gb->m_myBM.m_ballets.push_back(std::shared_ptr<Ballet>(new BalletAVR(
	&(m_gb->m_myBM),
	L"orangeBallet",
	m_color.value(),
	burstPos1,
	-3.00,
	Circular3(targetPos - burstPos1).theta,
	1.2,
	0.0,
	ScheduleTimer({10, 20, 30}))));

	m_gb->m_myBM.m_ballets.push_back(std::shared_ptr<Ballet>(new BalletAVR(
		&(m_gb->m_myBM),
		L"orangeBallet",
		m_color.value(),
		burstPos2,
		-3.00,
		Circular3(targetPos - burstPos2).theta,
		1.2,
		0.0,
		ScheduleTimer({ 10, 20, 30 }))));

	SoundAsset(L"MyBallet").playMulti();

	m_count = m_interval;
}

PurpleShot1::PurpleShot1(GameBase* gb) :Shot(gb, 60, ShimiColors::Purple)
{}

void PurpleShot1::draw(const Vec2& pos, const Vec2& v)const
{
	if (m_life <= 0) return;

	DrawTexAsShot(pos, v.rotated(m_theta), m_tex, Vec2(250, 250), Vec2(100, 0), false);

	/*
	const Vec2 rVec = Vec2(100, 0);

	const Vec2 pos = D2Camera::I()->getDrawPos(pos);

	const double theta = Circular(v).theta;

	const Vec2 posD = pos + rVec.rotated(theta + m_theta) - Vec2(250, 250);
	tex.rotateAt(rotPos, theta).draw(posD);

	if (!isMirror) return;

	const Vec2 posDmir = pos + Vec2(-relPos.x, relPos.y).rotated(theta) - rotPosMir;
	tex.mirror().rotateAt(rotPosMir, theta).draw(posDmir);
	*/
}

void PurpleShot1::drawFrame(const Vec2& pos, const Vec2& v)const
{
	if (m_life <= 0) return;

	DrawTexAsShot(pos, v.rotated(m_theta), m_frameTex, Vec2(250, 250), Vec2(100, 0), false);

}

void PurpleShot1::shot(const Vec2& pos, const Vec2& v)
{
	if (m_count > 0) return;

	if (m_life <= 0) return;

	const auto& c = m_gb->getNearestEnemyPos();

	const Vec2 targetPos = c ? c.value() : (getPosFromRelativeLocationFromMV(m_gb, Vec2(0, -120)));

	m_gb->m_myBM.m_ballets.push_back(std::shared_ptr<Ballet>(new BalletAVR(
		&(m_gb->m_myBM),
		L"purpleBallet",
		m_color.value(),
		pos,
		5.00,
		Circular3(v).theta,
		0.0,
		0.0,
		ScheduleTimer({ 20, 40, 60, 80, 100 }))));

	SoundAsset(L"MyBallet").playMulti();

	--m_life;
	m_lifeTimer = 300;
	m_count = m_interval;
}

void PurpleShot1::texUpdate()
{
	m_theta -= 0.01;

	if (m_lifeTimer > 0) --m_lifeTimer;
	else if (m_lifeTimer == 0 && m_life <= 0)
	{
		++m_life;
		if (m_life <= 0) m_lifeTimer = 300;
	}
}

int PurpleShot1::m_life = 1;

int PurpleShot1::m_lifeTimer = 0;

void WhiteShot::shot(const Vec2& pos, const Vec2& v)
{
	if (m_count > 0) return;

	
	m_gb->m_myBM.m_ballets.push_back(std::shared_ptr<Ballet>(new BalletAVR(
		&(m_gb->m_myBM),
		L"whiteBallet",
		none,
		m_gb->getMyVehiclePos(),
		5.00,
		Circular3(m_gb->m_mv.m_v).theta,
		0.0,
		0.0)));

	SoundAsset(L"MyBallet").playMulti();

	m_count = m_interval;
}