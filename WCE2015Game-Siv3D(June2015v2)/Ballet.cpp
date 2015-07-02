#include"Ballet.hpp"
#include"BalletManager.hpp"

using namespace shimi;

Ballet::Ballet(BalletManager* bm, const FilePath& path, const Vec2& pos) :m_manager(bm), m_image(path), m_tex(path), m_pos(pos)
{
}