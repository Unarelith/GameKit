#------------------------------------------------------------------------------
# CMake configuration
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME gamekit)

project(${PROJECT_NAME})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" "${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2")

add_subdirectory(source)

if (WIN32)
	set(WIN_LIBRARIES_PATH "C:/Libraries")
endif ()

#------------------------------------------------------------------------------
# Add executables
#------------------------------------------------------------------------------
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

add_dependencies(${PROJECT_NAME} sfml-system sfml-network sfml-graphics sfml-audio sfml-window)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/external
)

#------------------------------------------------------------------------------
# Setup install rule
#------------------------------------------------------------------------------
include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}-export
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	#INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/gk DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#------------------------------------------------------------------------------
# Compiler flags
#------------------------------------------------------------------------------
target_compile_options(${PROJECT_NAME} PRIVATE -g)
target_compile_options(${PROJECT_NAME} PRIVATE -DDEBUG_ENABLED -DDEBUG_COLOR)

if(NOT MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wfatal-errors)
	target_compile_options(${PROJECT_NAME} PUBLIC -Wno-variadic-macros)
endif()

if(MSVC)
	set(CMAKE_CXX_STANDARD 14)
else()
	target_compile_options(${PROJECT_NAME} PUBLIC -std=c++14)
endif()

# target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

#------------------------------------------------------------------------------
# Packages
#------------------------------------------------------------------------------
# - tinyxml2
#------------------------------------------------------------------------------
if (WIN32)
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${WIN_LIBRARIES_PATH}/tinyxml2)
endif ()

find_package(TinyXml2 REQUIRED)
if(NOT TINYXML2_FOUND)
	message(FATAL_ERROR "tinyxml2 is needed to build the project. Please install it correctly.")
endif()

include_directories(${TINYXML2_INCLUDE_DIRS})
link_directories(${TINYXML2_LIBRARY_DIRS})

#------------------------------------------------------------------------------
# - OpenGL
#------------------------------------------------------------------------------
set(OpenGL_GL_PREFERENCE "LEGACY")

if (WIN32)
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${WIN_LIBRARIES_PATH}/glm)
endif ()

find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)

if(NOT OPENGL_FOUND)
	message(FATAL_ERROR "OpenGL not found!")
endif(NOT OPENGL_FOUND)

if(NOT GLM_FOUND)
	message(FATAL_ERROR "glm not found!")
endif(NOT GLM_FOUND)

include_directories(${GLM_INCLUDE_DIRS})

#------------------------------------------------------------------------------
# - GLEW
#------------------------------------------------------------------------------
if (WIN32)
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${WIN_LIBRARIES_PATH}/glew)

	find_package(GLEW REQUIRED)

	if(NOT GLEW_FOUND)
		message(FATAL_ERROR "GLEW not found!")
	endif(NOT GLEW_FOUND)

	include_directories(${GLEW_INCLUDE_DIRS})
endif ()

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
# - SFML network
#------------------------------------------------------------------------------
add_subdirectory(external/SFML)

