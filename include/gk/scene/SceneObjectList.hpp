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
#ifndef GK_SCENEOBJECTLIST_HPP_
#define GK_SCENEOBJECTLIST_HPP_

#include <algorithm>
#include <deque>

#include "gk/scene/SceneObject.hpp"

namespace gk {

class SceneObjectList {
	using iterator = std::deque<SceneObject>::iterator;
	using const_iterator = std::deque<SceneObject>::const_iterator;

	public:
		SceneObject &addObject(SceneObject &&object) {
			m_objects.emplace_back(std::move(object));
			return m_objects.back();
		}

		SceneObject *findByName(const std::string &name) {
			auto it = std::find_if(m_objects.begin(), m_objects.end(), [name] (SceneObject &object) { return object.name() == name; });
			if (it == m_objects.end())
				return nullptr;
			else
				return &*it;
		}

		void removeByName(const std::string &name) {
			auto it = std::find_if(m_objects.begin(), m_objects.end(), [name] (SceneObject &object) { return object.name() == name; });
			if (it != m_objects.end())
				m_objects.erase(it);
		}

		void pop() { m_objects.pop_back(); }

		SceneObject &operator[](size_t n) { return m_objects[n]; }

		void remove(size_t n) { m_objects.erase(m_objects.begin() + n); }

		iterator begin() noexcept { return m_objects.begin(); }
		iterator end() noexcept { return m_objects.end(); }

		const_iterator begin() const noexcept { return m_objects.begin(); }
		const_iterator end() const noexcept { return m_objects.end(); }

		size_t size() const { return m_objects.size(); }

	private:
		std::deque<SceneObject> m_objects;
};

} // namespace gk

#endif // GK_SCENEOBJECTLIST_HPP_
