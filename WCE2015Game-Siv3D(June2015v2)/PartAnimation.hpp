#pragma once
#pragma warning (disable : 4018)
#include<Siv3D.hpp>


struct PTexture
{
	Texture m_tex;

	//基準からの相対位置
	Vec2 m_relPos;

	//接続点 表示位置や回転の支点は画像中のこの位置を基準になされる
	Vec2 m_rotPos;

	//画像を左右反転して扱うかどうか rotPosも自動的に左右反転する（画像中の位置のみを指定する）
	bool m_isMirror;

	PTexture getMirrored()
	{
		PTexture temp = { m_tex, m_relPos, m_rotPos, true };

		return temp;
	}

	//partPos…パーツの位置ずれ partTheta…パーツの回転
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
			//パーツの回転は標準時と逆（右回り）
			m_tex.mirror().rotateAt(rotPosMir, baseTheta + -partTheta).draw(posDmir, diffuse);
		}
	}
};

//srcのPTextureをdestのPTextureのdestPos部分にくっつけたようなPTextureを返す
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
