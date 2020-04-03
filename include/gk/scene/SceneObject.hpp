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
#ifndef GK_SCENEOBJECT_HPP_
#define GK_SCENEOBJECT_HPP_

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "gk/core/Exception.hpp"

namespace gk {

class SceneObject {
	public:
		SceneObject(const std::string &name = "null", const std::string &type = "null")
			: m_name(name), m_type(type) {}

		template<typename T, typename... Args>
		T &set(Args &&...args) {
			m_components[typeid(T).hash_code()] = std::make_shared<T>(std::forward<Args>(args)...);
			return get<T>();
		}

		template<typename T>
		bool has() const {
			return m_components.count(typeid(T).hash_code()) == 1;
		}

		template<typename T>
		T &get() const {
			auto it = m_components.find(typeid(T).hash_code());
			if(it == m_components.end()) {
				throw EXCEPTION("SceneObject", (void*)this, "(\"" + m_name + "\", \"" + m_type + "\") doesn't have a component of type:", typeid(T).name());
			}

			return *std::static_pointer_cast<T>(it->second);
		}

		template<typename T>
		void remove() {
			m_components.erase(typeid(T).hash_code());
		}

		void debug() const {
			gkDebug() << "=== Component list of object:" << (void*)this << "===";
			gkDebug() << "=== List address:" << (void*)&m_components;

			for(auto &it : m_components) {
				gkDebug() << it.first << ":" << (void*)it.second.get();
			}

			gkDebug() << "=== End of list. ===";
		}

		const std::string &name() const { return m_name; }
		const std::string &type() const { return m_type; }

	private:
		std::string m_name;
		std::string m_type;

		std::unordered_map<size_t, std::shared_ptr<void>> m_components;
};

} // namespace gk

#endif // GK_SCENEOBJECT_HPP_
