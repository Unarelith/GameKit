/*
 * =====================================================================================
 *
 *       Filename:  Scene.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:34:20
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_SCENE_HPP_
#define GK_SCENE_HPP_

#include <functional>
#include <list>

#include <SFML/Graphics/Drawable.hpp>

#include "gk/scene/controller/AbstractController.hpp"
#include "gk/scene/view/AbstractView.hpp"
#include "gk/scene/CollisionHelper.hpp"
#include "gk/scene/SceneObject.hpp"
#include "gk/scene/SceneObjectList.hpp"

namespace gk {

class Scene : public sf::Drawable {
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

		void draw(const SceneObject &object, sf::RenderTarget &target, sf::RenderStates states) const;

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		SceneObjectList m_objects;

		std::list<std::unique_ptr<AbstractController>> m_controllerList;
		std::list<std::unique_ptr<AbstractView>> m_viewList;

		std::unique_ptr<CollisionHelper> m_collisionHelper;
};

} // namespace gk

#endif // GK_SCENE_HPP_
