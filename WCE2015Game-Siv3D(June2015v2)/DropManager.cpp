#include"DropManager.hpp"
#include"Camera.hpp"

using namespace shimi;

void DropManager::draw()const
{
	for (const auto& drop : m_drops)
	{
		TextureAsset(drop.m_tag).rotate(drop.m_theta + Pi / 2.0).drawAt(D2Camera::I()->getDrawPos(drop.m_pos));
	}
}

