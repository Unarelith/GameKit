/*
 * =====================================================================================
 *
 *  GameKit
 *
 *  Copyright (C) 2018-2020 Unarelith, Quentin Bazin <openminer@unarelith.net>
 *  Copyright (C) 2020 the GameKit contributors (see CONTRIBUTORS.md)
 *
 *  This file is part of GameKit.
 *
 *  GameKit is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  GameKit is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with GameKit; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * =====================================================================================
 */
#include "gk/gl/GLCheck.hpp"
#include "gk/gl/Drawable.hpp"
#include "gk/gl/RenderTarget.hpp"
#include "gk/gl/Shader.hpp"
#include "gk/gl/Texture.hpp"
#include "gk/gl/Vertex.hpp"
#include "gk/gl/VertexBuffer.hpp"

namespace gk {

const RenderStates RenderStates::Default{};

RenderTarget::RenderTarget() {
	m_attributes.emplace_back(VertexAttribute::Coord3d, "coord3d", 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid *>(offsetof(Vertex, coord3d)));
	m_attributes.emplace_back(VertexAttribute::Color, "color", 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid *>(offsetof(Vertex, color)));
	m_attributes.emplace_back(VertexAttribute::TexCoord, "texCoord", 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid *>(offsetof(Vertex, texCoord)));
}

void RenderTarget::addVertexAttribute(u16 id, const std::string &name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) {
	m_attributes.emplace_back(id, name, size, type, normalized, stride, pointer);
}

void RenderTarget::clearVertexAttributes() {
	m_attributes.clear();
}

void RenderTarget::draw(const Drawable &drawable, const RenderStates &states) {
	drawable.draw(*this, states);
}

void RenderTarget::draw(const VertexBuffer &vertexBuffer, GLenum mode, std::size_t firstVertex, std::size_t vertexCount, const RenderStates &states) {
	VertexBuffer::bind(&vertexBuffer);
	beginDrawing(states);
	glCheck(glDrawArrays(mode, firstVertex, vertexCount));
	endDrawing(states);
}

void RenderTarget::drawElements(const VertexBuffer &vertexBuffer, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, const RenderStates &states) {
	VertexBuffer::bind(&vertexBuffer);
	beginDrawing(states);
	glCheck(glDrawElements(mode, count, type, indices));
	endDrawing(states);
}

void RenderTarget::beginDrawing(const RenderStates &states) {
	if (!states.shader) return;

	Shader::bind(states.shader);

	if (!m_view) {
		states.shader->setUniform("u_projectionMatrix", states.projectionMatrix);
		states.shader->setUniform("u_viewMatrix", states.viewMatrix);
	}
	else if (m_viewChanged)
		applyCurrentView(states);

	states.shader->setUniform("u_modelMatrix", states.transform);

	for (VertexAttributeData &attr : m_attributes) {
		if (states.vertexAttributes & attr.id) {
			states.shader->enableVertexAttribArray(attr.name);
			glCheck(glVertexAttribPointer(states.shader->attrib(attr.name), attr.size, attr.type, attr.normalized, attr.stride, attr.pointer));
		}
	}

	if (states.texture)
		Texture::bind(states.texture);
}

void RenderTarget::endDrawing(const RenderStates &states) {
	if (!states.shader) return;

	for (VertexAttributeData &attr : m_attributes) {
		if (states.vertexAttributes & attr.id) {
			states.shader->disableVertexAttribArray(attr.name);
		}
	}

	VertexBuffer::bind(nullptr);
}

IntRect RenderTarget::getViewport(const View& view) const {
	float width  = static_cast<float>(getSize().x);
	float height = static_cast<float>(getSize().y);
	const FloatRect& viewport = view.getViewport();

	return IntRect(static_cast<int>(0.5f + width  * viewport.x),
	               static_cast<int>(0.5f + height * viewport.y),
	               static_cast<int>(width  * viewport.sizeX),
	               static_cast<int>(height * viewport.sizeY));
}

void RenderTarget::applyCurrentView(const RenderStates &states) {
	IntRect viewport = getViewport(*m_view);
	if (viewport != m_previousViewport) {
		int top = getSize().y - (viewport.y + viewport.sizeY);
		glViewport(viewport.x, top, viewport.sizeX, viewport.sizeY);
		m_previousViewport = viewport;
	}

	states.shader->setUniform("u_projectionMatrix", m_view->getTransform());
	states.shader->setUniform("u_viewMatrix", m_view->getViewTransform());

	m_viewChanged = false;
}

} // namespace gk

