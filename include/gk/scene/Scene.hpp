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
#ifndef GK_SCENE_HPP_
#define GK_SCENE_HPP_

#include <functional>
#include <list>

#include "gk/gl/Drawable.hpp"
#include "gk/scene/controller/AbstractController.hpp"
#include "gk/scene/view/AbstractView.hpp"
#include "gk/scene/CollisionHelper.hpp"
#include "gk/scene/SceneObject.hpp"
#include "gk/scene/SceneObjectList.hpp"

namespace gk {

class Scene : public Drawable {
	public:
		Scene();

		void reset();
		void update();

		void reset(SceneObject &object);
		void update(SceneObject &object);

		SceneObject &addObject(SceneObject &&object);

		void addCollisionChecker(std::function<void(SceneObject &)> checker);
		void checkCollisionsFor(SceneObject &object);

		SceneObjectList &objects() { return m_objects; }
		const SceneObjectList &objects() const { return m_objects; }

		template<typename T, typename... Args>
		auto addController(Args &&...args) -> typename std::enable_if<std::is_base_of<AbstractController, T>::value, T&>::type {
			m_controllerList.emplace_back(new T(std::forward<Args>(args)...));
			return *static_cast<T*>(m_controllerList.back().get());
		}

		template<typename T, typename... Args>
		auto addView(Args &&...args) -> typename std::enable_if<std::is_base_of<AbstractView, T>::value, T&>::type {
			m_viewList.emplace_back(new T(std::forward<Args>(args)...));
			return *static_cast<T*>(m_viewList.back().get());
		}

		template<typename T, typename... Args>
		auto setCollisionHelper(Args &&...args) -> typename std::enable_if<std::is_base_of<CollisionHelper, T>::value, T&>::type {
			m_collisionHelper.reset(new T(std::forward<Args>(args)...));
			return *static_cast<T*>(m_collisionHelper.get());
		}

		bool isActive() { return !m_controllerList.empty() || !m_viewList.empty(); }

		void draw(const SceneObject &object, RenderTarget &target, RenderStates states) const;

	private:
		void draw(RenderTarget &target, RenderStates states) const override;

		SceneObjectList m_objects;

		std::list<std::unique_ptr<AbstractController>> m_controllerList;
		std::list<std::unique_ptr<AbstractView>> m_viewList;

		std::unique_ptr<CollisionHelper> m_collisionHelper;
};

} // namespace gk

#endif // GK_SCENE_HPP_
