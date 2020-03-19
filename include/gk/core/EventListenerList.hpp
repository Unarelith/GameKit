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
#ifndef GK_EVENTLISTENERLIST_HPP_
#define GK_EVENTLISTENERLIST_HPP_

#include <functional>
#include <queue>
#include <vector>

#include "gk/core/IntTypes.hpp"

namespace gk {

class IEventListenerList {
	public:
		virtual ~IEventListenerList() = default;

		virtual void processEvents() = 0;

		virtual void removeListeners(void *instance) = 0;
};

template<typename T>
class EventListenerList : public IEventListenerList {
	public:
		void addListener(std::function<void(const T &)> &&function) {
			m_listeners.emplace_back(function, nullptr);
		}

		void addListener(std::function<void(const T &)> &&function, void *instance) {
			m_listeners.emplace_back(function, instance);
		}

		void removeListeners(void *instance) override {
			for (auto it = m_listeners.begin() ; it != m_listeners.end() ;) {
				if (it->second == instance)
					m_listeners.erase(it);
				else
					++it;
			}
		}

		void pushEvent(const T &event) {
			m_events.emplace(event);
		}

		template<typename... Args>
		void emplaceEvent(Args &&...args) {
			m_events.emplace(std::forward<Args>(args)...);
		}

		void processEvents() override {
			while (!m_events.empty()) {
				const T &event = m_events.front();
				m_events.pop();
				for (auto &listener : m_listeners) {
					listener.first(event);
				}
			}
		}

	private:
		std::queue<T> m_events;
		std::vector<std::pair<std::function<void(const T &)>, void *>> m_listeners;
};

} // namespace gk

#endif // GK_EVENTLISTENERLIST_HPP_
