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
#ifndef GK_BEHAVIOURCOMPONENT_HPP_
#define GK_BEHAVIOURCOMPONENT_HPP_

#include <unordered_map>

#include "gk/scene/behaviour/Behaviour.hpp"

namespace gk {

class BehaviourComponent {
	public:
		template<typename T, typename... Args>
		T &addBehaviour(const char *name, Args &&...args) {
			T *t = new T(std::forward<Args>(args)...);
			m_behaviours.emplace(name, t);
			return *t;
		}

		void update(SceneObject &object) {
			for (auto &it : m_behaviours) {
				it.second->update(object);
			}
		}

	private:
		std::unordered_map<std::string, std::unique_ptr<Behaviour>> m_behaviours;
};

} // namespace gk

#endif // GK_BEHAVIOURCOMPONENT_HPP_
