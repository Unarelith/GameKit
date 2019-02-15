/*
 * =====================================================================================
 *
 *       Filename:  Image.hpp
 *
 *    Description:
 *
 *        Created:  20/09/2014 16:21:56
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_IMAGE_HPP_
#define GK_IMAGE_HPP_

#include "gk/graphics/Color.hpp"
#include "gk/core/Rect.hpp"
#include "gk/gl/IDrawable.hpp"
#include "gk/gl/Transformable.hpp"
#include "gk/gl/VertexBuffer.hpp"

namespace gk {

class Image : public IDrawable, public Transformable {
	public:
		Image() = default;
		Image(const std::string &textureName);
		Image(const Texture &texture);

		void load(const Image &image);
		void load(const std::string &textureName);
		void load(const Texture &texture);

		const FloatRect &clipRect() const { return m_clipRect; }
		void setClipRect(float x, float y, u16 width, u16 height);

		u16 width() const { return m_width * getScale().x; }
		u16 height() const { return m_height * getScale().y; }

		void setColor(const Color &color) { m_color = color; updateVertexBuffer(); }
		void setFlip(bool isFlipped) { m_isFlipped = isFlipped; }

	protected:
		void updateVertexBuffer() const;

		void draw(RenderTarget &target, RenderStates states) const override;

		const Texture *m_texture = nullptr;

		VertexBuffer m_vbo;

	private:
		u16 m_width = 0;
		u16 m_height = 0;

		FloatRect m_clipRect;

		Color m_color;

		bool m_isFlipped = false;
};

} // namespace gk

#endif // GK_IMAGE_HPP_
