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

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>

#include "gk/core/IntTypes.hpp"

namespace gk {

class Image : public sf::Drawable, public sf::Transformable {
	public:
		Image();
		Image(const std::string &textureName);
		Image(const sf::Texture &texture);

		void load(const Image &image);
		void load(const std::string &textureName);
		void load(const sf::Texture &texture);

		const sf::FloatRect &clipRect() const { return m_clipRect; }
		void setClipRect(float x, float y, u16 width, u16 height);

		const sf::FloatRect &posRect() const { return m_posRect; }
		void setPosRect(float x, float y, u16 width, u16 height);

		u16 width() const { return m_width * getScale().x; }
		u16 height() const { return m_height * getScale().y; }

		void setColor(const sf::Color &color) { m_color = color; updateVertexBuffer(); }
		void setAlphaMod(u8 alpha) { m_color.a = alpha / 255.0f; updateVertexBuffer(); }
		void setFlip(bool isFlipped) { m_isFlipped = isFlipped; }

	protected:
		void updateVertexBuffer();

		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		const sf::Texture *m_texture = nullptr;

		sf::VertexBuffer m_vertices;

	private:
		u16 m_width = 0;
		u16 m_height = 0;

		sf::FloatRect m_clipRect;
		sf::FloatRect m_posRect;

		sf::Color m_color = sf::Color::White;

		bool m_isFlipped = false;
};

} // namespace gk

#endif // GK_IMAGE_HPP_
