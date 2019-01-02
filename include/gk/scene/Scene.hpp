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

#include "gk/gl/IDrawable.hpp"
#include "gk/scene/controller/AbstractController.hpp"
#include "gk/scene/view/AbstractView.hpp"
#include "gk/scene/SceneObject.hpp"
#include "gk/scene/SceneObjectList.hpp"

namespace gk {

class Scene : public IDrawable {
	public:
		void reset();
		void update();

		SceneObject &addObject(SceneObject &&object);

		void addCollisionChecker(std::function<void(SceneObject &)> checker);
		void checkCollisionsFor(SceneObject &object);

		SceneObjectList &objects() { return m_objects; }
		const SceneObjectList &objects() const { return m_objects; }

		template<typename T, typename... Args>
		auto addController(Args &&...args) -> typename std::enable_if<std::is_base_of<AbstractController, T>::value, T&>::type {
			m_controllerList.emplace_back(new T(std::forward<Args>(args)...));
			return *dynamic_cast<T*>(m_controllerList.back().get());
		}

		template<typename T, typename... Args>
		auto addView(Args &&...args) -> typename std::enable_if<std::is_base_of<AbstractView, T>::value, T&>::type {
			m_viewList.emplace_back(new T(std::forward<Args>(args)...));
			return *dynamic_cast<T*>(m_viewList.back().get());
		}

		bool isActive() { return !m_controllerList.empty() || !m_viewList.empty(); }

	private:
		void draw(RenderTarget &target, RenderStates states) const override;

		SceneObjectList m_objects;

		std::list<std::unique_ptr<AbstractController>> m_controllerList;
		std::list<std::unique_ptr<AbstractView>> m_viewList;
};

} // namespace gk

#endif // GK_SCENE_HPP_
