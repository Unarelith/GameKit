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
#ifndef GK_CONFIG_HPP_
#define GK_CONFIG_HPP_

////////////////////////////////////////////////////////////
// Identify the operating system
// see http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
// and SFML/Config.hpp
////////////////////////////////////////////////////////////
#if defined(_WIN32)
	// Windows
	#define GK_SYSTEM_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
	// Apple platform, see which one it is
	#include "TargetConditionals.h"

	#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
		// iOS
		#define GK_SYSTEM_IOS
	#elif TARGET_OS_MAC
		// MacOS
		#define GK_SYSTEM_MACOS
	#else
		// Unsupported Apple system
		#error This Apple operating system is not supported by GameKit library
	#endif
#elif defined(__unix__)
	// UNIX system, see which one it is
	#if defined(__ANDROID__)
		// Android
		#define GK_SYSTEM_ANDROID
	#elif defined(__linux__)
		// Linux
		#define GK_SYSTEM_LINUX
	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
		// FreeBSD
		#define GK_SYSTEM_FREEBSD
	#elif defined(__OpenBSD__)
		// OpenBSD
		#define GK_SYSTEM_OPENBSD
	#else
		// Unsupported UNIX system
		#error This UNIX operating system is not supported by GameKit library
	#endif
#else
	// Unsupported system
	#error This operating system is not supported by GameKit library
#endif

#endif // GK_CONFIG_HPP_
