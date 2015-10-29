#include"Ballet.hpp"
#include"DropManager.hpp"

using namespace shimi;

void BalletAVR::drop()
{
	DropManager::I()->m_drops.push_back(Drop(m_balletPictureLabel, m_pos, dir));
}