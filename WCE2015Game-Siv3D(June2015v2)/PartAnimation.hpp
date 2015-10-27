#pragma once
#pragma warning (disable : 4018)
#include<Siv3D.hpp>


struct PTexture
{
	Texture m_tex;

	//�����̑��Έʒu
	Vec2 m_relPos;

	//�ڑ��_ �\���ʒu���]�̎x�_�͉摜���̂��̈ʒu����ɂȂ����
	Vec2 m_rotPos;

	//�摜�����E���]���Ĉ������ǂ��� rotPos�������I�ɍ��E���]����i�摜���̈ʒu�݂̂��w�肷��j
	bool m_isMirror;

	PTexture getMirrored()
	{
		PTexture temp = { m_tex, m_relPos, m_rotPos, true };

		return temp;
	}

	//partPos�c�p�[�c�̈ʒu���� partTheta�c�p�[�c�̉�]
	void draw(const Vec2& basePos, const double baseTheta, const Vec2& partPos = Vec2(0, 0), const double partTheta = 0, const Color& diffuse = Palette::White)const
	{
		if (!m_isMirror)
		{

			const Vec2 posD = basePos + (m_relPos + partPos).rotated(baseTheta) - m_rotPos;
			m_tex.rotateAt(m_rotPos, baseTheta + partTheta).draw(posD, diffuse);
		}
		else
		{
			const Vec2 rotPosMir = Vec2{ (m_tex.size.x - m_rotPos.x), m_rotPos.y };
			const Vec2 posDmir = basePos + (Vec2(-m_relPos.x, m_relPos.y) + Vec2(-partPos.x, partPos.y)).rotated(baseTheta) - rotPosMir;
			//�p�[�c�̉�]�͕W�����Ƌt�i�E���j
			m_tex.mirror().rotateAt(rotPosMir, baseTheta + -partTheta).draw(posDmir, diffuse);
		}
	}
};

//src��PTexture��dest��PTexture��destPos�����ɂ��������悤��PTexture��Ԃ�
PTexture Attach(const PTexture& dest, const PTexture& src, const Vec2& destPos);

template <typename T>
struct FrameData
{
	int m_time;
	T m_value;
};

template <typename T>
class FrameExp
{
public:
	int m_count = 0;

	int m_phase = 0;

	std::vector<FrameData<T>> m_values;

	FrameExp()
	{}

	void update()
	{

		++m_count;

		if (!(m_count < m_values[m_phase].m_time))
		{
			m_count = 0;
			++m_phase;

			if (m_phase >= m_values.size()) m_phase = 0;
		}		
	}

	T getData()const
	{
		return m_values[m_phase].m_value;
	}

	void timerReset()
	{
		m_phase = 0;
		m_count = 0;
	}

	void dataReset()
	{
		timerReset();
		m_values.clear();
	}
	

};
