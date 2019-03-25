/*
 * =====================================================================================
 *
 *       Filename:  Image.cpp
 *
 *    Description:
 *
 *        Created:  20/09/2014 16:22:12
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include "gk/graphics/Image.hpp"
#include "gk/resource/ResourceHandler.hpp"

namespace gk {

Image::Image() {
	m_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
	m_vertices.create(4);
}

Image::Image(const std::string &textureName) : Image() {
	load(ResourceHandler::getInstance().get<sf::Texture>(textureName));
}

Image::Image(const sf::Texture &texture) : Image() {
	load(texture);
}

void Image::load(const Image &image) {
	m_texture = image.m_texture;

	m_width = image.m_width;
	m_height = image.m_height;

	m_clipRect = image.m_clipRect;
	m_posRect = image.m_posRect;

	m_color = image.m_color;

	updateVertexBuffer();
}

void Image::load(const std::string &textureName) {
	load(ResourceHandler::getInstance().get<sf::Texture>(textureName));
}

void Image::load(const sf::Texture &texture) {
	m_texture = &texture;

	m_width = m_texture->getSize().x;
	m_height = m_texture->getSize().y;

	setClipRect(0, 0, m_width, m_height);
	setPosRect(0, 0, m_width, m_height);
}

void Image::setClipRect(float x, float y, u16 width, u16 height) {
	m_clipRect = sf::FloatRect(x, y, width, height);

	m_posRect.width = width;
	m_posRect.height = height;

	updateVertexBuffer();
}

void Image::setPosRect(float x, float y, u16 width, u16 height) {
	m_posRect = sf::FloatRect(x, y, width, height);

	updateVertexBuffer();
}

void Image::updateVertexBuffer() {
	sf::Vertex vertices[4] = {
		{{m_posRect.left + m_posRect.width, m_posRect.top,                  }},
		{{m_posRect.left,                   m_posRect.top,                  }},
		{{m_posRect.left,                   m_posRect.top + m_posRect.height}},
		{{m_posRect.left + m_posRect.width, m_posRect.top + m_posRect.height}},
	};

	if (!m_isFlipped) {
		vertices[0].texCoords.x = m_clipRect.left + m_clipRect.width;
		vertices[0].texCoords.y = m_clipRect.top;
		vertices[1].texCoords.x = m_clipRect.left;
		vertices[1].texCoords.y = m_clipRect.top;
		vertices[2].texCoords.x = m_clipRect.left;
		vertices[2].texCoords.y = m_clipRect.top  + m_clipRect.height;
		vertices[3].texCoords.x = m_clipRect.left + m_clipRect.width;
		vertices[3].texCoords.y = m_clipRect.top  + m_clipRect.height;
	}
	else {
		vertices[0].texCoords.x = m_clipRect.left;
		vertices[0].texCoords.y = m_clipRect.top;
		vertices[1].texCoords.x = m_clipRect.left + m_clipRect.width;
		vertices[1].texCoords.y = m_clipRect.top;
		vertices[2].texCoords.x = m_clipRect.left + m_clipRect.width;
		vertices[2].texCoords.y = m_clipRect.top  + m_clipRect.height;
		vertices[3].texCoords.x = m_clipRect.left;
		vertices[3].texCoords.y = m_clipRect.top + m_clipRect.height;
	}

	for (u8 i = 0 ; i < 4 ; ++i) {
		vertices[i].color = m_color;
	}

	m_vertices.update(vertices);
}

void Image::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();

	states.texture = m_texture;

	target.draw(m_vertices, states);
}

}

