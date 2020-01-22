/*
 * =====================================================================================
 *
 *       Filename:  OpenGL.hpp
 *
 *    Description:
 *
 *        Created:  15/12/2014 04:18:34
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_OPENGL_HPP_
#define GK_OPENGL_HPP_

#define GL_GLEXT_PROTOTYPES
#define GL3_PROTOTYPES 1

#ifdef __APPLE__
	#include <OpenGL/gl.h>
#else
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(__MINGW32__)
		#ifdef USE_GLAD
			#include <GLAD/glad.h>
		#else
			#include <GL/glew.h>
		#endif
	#else
		#include <GL/gl.h>
	#endif
#endif

#endif // GK_OPENGL_HPP_
