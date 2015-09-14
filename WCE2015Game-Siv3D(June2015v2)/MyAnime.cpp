# include "MyAnime.hpp"

using namespace shimi;

MyAnime::MyAnime() {}

MyAnime::MyAnime(const String& texTag, unsigned size, unsigned count) :
m_texTag(texTag),
m_size(size),
m_frame(size, count),
m_index(0),
m_count(0) {}

MyAnime::MyAnime(const String& texTag, unsigned size, const Array<unsigned>& frame):
m_texTag(texTag),
m_size(size),
m_frame(frame),
m_index(0),
m_count(0) {}

inline unsigned MyAnime::size() const
{
	return m_size;
}

inline unsigned MyAnime::index() const
{
	return m_index;
}

inline unsigned MyAnime::count() const
{
	return m_count;
}

void MyAnime::setFrame(unsigned count)
{
	m_frame = Array<unsigned>(m_size, count);
}

void MyAnime::setFrame(const Array<unsigned>& frame)
{
#ifdef _DEBUG
	if (frame.size() != m_size)
	{
		LOG(L"asc::MyAnime frameの枚数がsizeと一致しません。");
	}
#endif
	m_frame = frame;
}

void MyAnime::update()
{
	while (m_count >= m_frame[m_index])
	{
		++m_index;
		m_count = 0;

		if (m_index >= m_size)
		{
			m_index = 0;
		}
	}

	++m_count;
}

void MyAnime::jump(unsigned index, unsigned count)
{
#ifdef _DEBUG
	if (index >= m_size)
	{
		LOG(L"asc::MyAnime jump関数で存在しないindexにアクセスしました。");
	}
#endif
	m_index = index;
	m_count = count;
}



inline double MyAnime::width() const
{
	return TextureAsset(m_texTag).width / m_size;
}

const RectF MyAnime::draw(const Color& diffuse) const
{
	return get().draw(diffuse);
}

const RectF MyAnime::draw(double x, double y, const Color& diffuse) const
{
	return get().draw(x, y, diffuse);
}

const RectF MyAnime::draw(const Vec2& pos, const Color& diffuse) const
{
	return get().draw(pos, diffuse);
}

const RectF MyAnime::drawAt(double x, double y, const Color& diffuse) const
{
	return get().drawAt(x, y, diffuse);
}

const RectF MyAnime::drawAt(const Vec2& pos, const Color& diffuse) const
{
	return get().drawAt(pos, diffuse);
}

const TextureRegion MyAnime::operator ()(double x, double y, double w, double h) const
{
	return TextureAsset(m_texTag)(m_index * width() + x, y, w, h);
}

const TextureRegion MyAnime::operator ()(const RectF& rect) const
{
	return TextureAsset(m_texTag)(m_index * width() + rect.x, rect.y, rect.w, rect.h);
}

const TextureRegion MyAnime::uv(double u, double v, double w, double h) const
{
	return TextureAsset(m_texTag).uv((m_index + u) / m_size, v, w / m_size, h);
}

const TextureRegion MyAnime::uv(const RectF& rect) const
{
	return TextureAsset(m_texTag).uv(rect.movedBy(m_index * width(), 0.0));
}

const TextureRegion MyAnime::mirror() const
{
	return get().mirror();
}

const TextureRegion MyAnime::flip() const
{
	return get().flip();
}

const TextureRegion MyAnime::scale(double scaling) const
{
	return get().scale(scaling);
}

const TextureRegion MyAnime::scale(double xScaling, double yScaling) const
{
	return get().scale(xScaling, yScaling);
}

const TextureRegion MyAnime::scale(const Vec2& scaling) const
{
	return get().scale(scaling);
}

const TextureRegion MyAnime::resize(double width, double height) const
{
	return get().resize(width, height);
}

const TextureRegion MyAnime::resize(const Vec2& size) const
{
	return get().resize(size);
}

const TexturedQuad MyAnime::rotate(double radian) const
{
	return get().rotate(radian);
}

const TexturedQuad MyAnime::rotateAt(double x, double y, double radian) const
{
	return get().rotateAt(x, y, radian);
}

const TexturedQuad MyAnime::rotateAt(const Vec2& pos, double radian) const
{
	return get().rotateAt(pos, radian);
}
