# pragma once

# include <Siv3D.hpp>

namespace asc
{
	using namespace s3d;

	/// <summary>
	/// �e�N�X�`���ŃA�j���[�V���������N���X
	/// </summary>
	class Anime
	{
	public:

		/// <summary>
		/// �f�t�H���g�R���X�g���N�^
		/// </summary>
		Anime();

		/// <summary>
		/// s3d::Texture����asc::Anime���쐬
		/// </summary>
		/// <param name="size">
		/// Texture�Ɋ܂܂��t���[���̐�
		/// </param>
		/// <param name="count">
		/// 1�t���[���̕`���
		/// </param>
		Anime(const Texture& texture, unsigned size, unsigned count);

		/// <summary>
		/// s3d::Texture����asc::Anime���쐬
		/// </summary>
		/// <param name="size">
		/// Texture�Ɋ܂܂��t���[���̐�
		/// </param>
		/// <param name="frame">
		/// �t���[���̐ݒ�
		/// </param>
		Anime(const Texture& texture, unsigned size, const Array<unsigned>& frame);

		/// <summary>
		/// ������Texture����ł͂Ȃ���
		/// </summary>
		/// <returns>
		/// �����̃e�N�X�`������ł͂Ȃ��ꍇ true, ����ȊO�̏ꍇ�� false
		/// </returns>
		explicit operator bool() const;

		/// <summary>
		/// ������Texture��Ԃ��܂�
		/// </summary>
		/// <returns>
		/// �����̃e�N�X�`��
		/// </returns>
		const Texture& texture() const;

		/// <summary>
		/// 1�t���[���̉���
		/// </summary>
		/// <returns>
		/// �����̑傫���i�s�N�Z���j
		/// </returns>
		double width() const;

		/// <summary>
		/// 1�t���[���̍���
		/// </summary>
		/// <returns>
		/// �����̑傫���i�s�N�Z���j
		/// </returns>
		double height() const;

		/// <summary>
		/// �����Ɋ܂܂��t���[���̌�
		/// </summary>
		/// <returns>
		/// �t���[���̌�
		/// </returns>
		unsigned size() const;

		/// <summary>
		/// ���݁A�ǂ̃t���[����`�ʂ��Ă��邩
		/// </summary>
		/// <returns>
		/// �t���[���̃C���f�b�N�X
		/// </returns>
		unsigned index() const;

		/// <summary>
		/// ���݂̃t���[��������`�ʂ�����
		/// </summary>
		/// <returns>
		/// �`�悵����
		/// </returns>
		unsigned count() const;

		/// <summary>
		/// �t���[���̕`����@��ݒ肷��
		/// </summary>
		/// <param name="count">
		/// 1�t���[���̕`���
		/// </param>
		void setFrame(unsigned count);

		/// <summary>
		/// �t���[���̕`����@��ݒ肷��
		/// </summary>
		/// <param name="frame">
		/// �t���[���̐ݒ�
		/// </param>
		void setFrame(const Array<unsigned>& frame);

		/// <summary>
		/// Anime�����̎��Ԃ�i�߂�
		/// </summary>
		void update();

		/// <summary>
		/// �w�肵���t���[���Ɉړ�����
		/// </summary>
		/// <param name="index">
		/// �ړ�����C���f�b�N�X
		/// </param>
		/// <param name="count">
		/// �ړ�����C���f�b�N�X�����O�ɉ���`�悷�邩
		/// </param>
		void jump(unsigned index, unsigned count = 0);

		/// <summary>
		/// �`�悷��e�N�X�`�����擾
		/// </summary>
		/// <returns>
		/// �`�悷��e�N�X�`��
		/// </returns>
		const TextureRegion get() const;

		/// <summary>
		/// s3d::Texture::draw
		/// </summary>
		const RectF draw(const Color& diffuse = Palette::White) const;

		/// <summary>
		/// s3d::Texture::draw
		/// </summary>
		const RectF draw(double x, double y, const Color& diffuse = Palette::White) const;

		/// <summary>
		/// s3d::Texture::draw
		/// </summary>
		const RectF draw(const Vec2& pos, const Color& diffuse = Palette::White) const;

		/// <summary>
		/// s3d::Texture::drawAt
		/// </summary>
		const RectF drawAt(double x, double y, const Color& diffuse = Palette::White) const;

		/// <summary>
		/// s3d::Texture::drawAt
		/// </summary>
		const RectF drawAt(const Vec2& pos, const Color& diffuse = Palette::White) const;

		/// <summary>
		/// s3d::Texture::operator
		/// </summary>
		const TextureRegion operator ()(double x, double y, double w, double h) const;

		/// <summary>
		/// s3d::Texture::operator
		/// </summary>
		const TextureRegion operator ()(const RectF& rect) const;

		/// <summary>
		/// s3d::Texture::uv
		/// </summary>
		const TextureRegion uv(double u, double v, double w, double h) const;

		/// <summary>
		/// s3d::Texture::uv
		/// </summary>
		const TextureRegion uv(const RectF& rect) const;

		/// <summary>
		/// s3d::Texture::mirror
		/// </summary>
		const TextureRegion mirror() const;

		/// <summary>
		/// s3d::Texture::flip
		/// </summary>
		const TextureRegion flip() const;

		/// <summary>
		/// s3d::Texture::scale
		/// </summary>
		const TextureRegion scale(double scaling) const;

		/// <summary>
		/// s3d::Texture::scale
		/// </summary>
		const TextureRegion scale(double xScaling, double yScaling) const;

		/// <summary>
		/// s3d::Texture::scale
		/// </summary>
		const TextureRegion scale(const Vec2& scaling) const;

		/// <summary>
		/// s3d::Texture::resize
		/// </summary>
		const TextureRegion resize(double width, double height) const;

		/// <summary>
		/// s3d::Texture::resize
		/// </summary>
		const TextureRegion resize(const Vec2& size) const;

		/// <summary>
		/// s3d::Texture::rotate
		/// </summary>
		const TexturedQuad rotate(double radian) const;

		/// <summary>
		/// s3d::Texture::rotateAt
		/// </summary>
		const TexturedQuad rotateAt(double x, double y, double radian) const;

		/// <summary>
		/// s3d::Texture::rotateAt
		/// </summary>
		const TexturedQuad rotateAt(const Vec2& pos, double radian) const;

	private:

		Texture m_texture;

		unsigned m_size;

		Array<unsigned> m_frame;

		unsigned m_index;

		unsigned m_count;
	};
}
