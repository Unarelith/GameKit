/*
 * =====================================================================================
 *
 *       Filename:  BehaviourComponent.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:45:23
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
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
