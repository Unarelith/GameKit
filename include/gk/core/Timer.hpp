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
#ifndef GK_TIMER_HPP_
#define GK_TIMER_HPP_

#include "gk/core/IntTypes.hpp"

namespace gk {

////////////////////////////////////////////////////////////
/// \brief Very basic timer
///
////////////////////////////////////////////////////////////
class Timer {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Constructor
		///
		/// \param useRealTime Use simulated time if true and by default, otherwise use system time.
		///
		////////////////////////////////////////////////////////////
		Timer(bool useRealTime = false);

		////////////////////////////////////////////////////////////
		/// \brief Stop the timer
		///
		////////////////////////////////////////////////////////////
		void stop();

		////////////////////////////////////////////////////////////
		/// \brief Start the timer
		///
		////////////////////////////////////////////////////////////
		void start();

		////////////////////////////////////////////////////////////
		/// \brief Reset the timer
		///
		////////////////////////////////////////////////////////////
		void reset();

		////////////////////////////////////////////////////////////
		/// \brief Get time
		///
		/// \return The time elapsed since last call to start() (in milliseconds)
		///
		////////////////////////////////////////////////////////////
		u32 time() const;

		////////////////////////////////////////////////////////////
		/// \brief Set time
		///
		/// \param time The new time value for this timer
		///
		////////////////////////////////////////////////////////////
		void setTime(u32 time);

		////////////////////////////////////////////////////////////
		/// \brief Check if the timer is started
		///
		/// \return True if the timer is started, false otherwise.
		///
		////////////////////////////////////////////////////////////
		bool isStarted() const { return m_isStarted; }

	private:
		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		bool m_useRealTime = false; ///< The timer will use system time instead of simulated time if set to true

		bool m_isStarted = false;   ///< Is true if the timer is running

		u32 m_t = 0;
		u32 m_tick = 0;
};

} // namespace gk

#endif // GK_TIMER_HPP_

////////////////////////////////////////////////////////////
/// \class gk::Timer
/// \ingroup core
///
/// This class is a very basic timer to help making animations, timed movements, and more.
///
////////////////////////////////////////////////////////////
