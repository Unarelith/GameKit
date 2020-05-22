#------------------------------------------------------------------------------
# CMake configuration
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME gamekit)

project(${PROJECT_NAME})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#------------------------------------------------------------------------------
# Packages
#------------------------------------------------------------------------------
# - OpenGL
#------------------------------------------------------------------------------
set(OpenGL_GL_PREFERENCE "LEGACY")

find_package(OpenGL REQUIRED)

if(NOT OPENGL_FOUND)
	message(FATAL_ERROR "OpenGL not found!")
endif(NOT OPENGL_FOUND)

#------------------------------------------------------------------------------
# Submodules
# from https://cliutils.gitlab.io/modern-cmake/chapters/projects/submodule.html
#------------------------------------------------------------------------------
find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
	option(GIT_SUBMODULE "Check submodules during build" ON)
	if(GIT_SUBMODULE)
		message(STATUS "Submodule update")
		execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			RESULT_VARIABLE GIT_SUBMOD_RESULT)
		if(NOT GIT_SUBMOD_RESULT EQUAL "0")
			message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
		endif()
	endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/SFML/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

#------------------------------------------------------------------------------
# - SFML
#------------------------------------------------------------------------------
set(SFML_STATIC TRUE)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(external/SFML)

#------------------------------------------------------------------------------
# - GLEW
#------------------------------------------------------------------------------
if (WIN32)
	set(glew-cmake_BUILD_STATIC ON)
	set(glew-cmake_BUILD_SHARED OFF)
	set(glew-cmake_BUILD_MULTI_CONTEXT OFF)

	add_subdirectory(external/glew)
endif ()

#------------------------------------------------------------------------------
# - glm
#------------------------------------------------------------------------------
add_subdirectory(external/glm)

#------------------------------------------------------------------------------
# - tinyxml2
#------------------------------------------------------------------------------
add_subdirectory(external/tinyxml2)

# Sources
add_subdirectory(source)

