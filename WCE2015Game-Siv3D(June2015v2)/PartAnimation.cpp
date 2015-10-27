#include"PartAnimation.hpp"

PTexture Attach(const PTexture& dest, const PTexture& src, const Vec2& destPos)
{

	PTexture temp = { src.m_tex, (dest.m_relPos - dest.m_rotPos + destPos + src.m_relPos), src.m_rotPos, src.m_isMirror };

	return temp;

}