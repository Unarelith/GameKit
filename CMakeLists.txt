#------------------------------------------------------------------------------
# CMake configuration
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.1)

project(gamekit VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(source)

#------------------------------------------------------------------------------
# Add executables
#------------------------------------------------------------------------------
add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${CMAKE_PROJECT_NAME}
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

install(TARGETS ${CMAKE_PROJECT_NAME}
	EXPORT ${CMAKE_PROJECT_NAME}-export
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	#INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/gk DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#------------------------------------------------------------------------------
# Compiler flags
#------------------------------------------------------------------------------
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -g)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Wfatal-errors)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -DDEBUG_ENABLED -DDEBUG_COLOR)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -Wno-variadic-macros)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -std=c++14)
# target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_14)

#------------------------------------------------------------------------------
# Packages
#------------------------------------------------------------------------------
# - tinyxml2
#------------------------------------------------------------------------------
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
# - SFML
#------------------------------------------------------------------------------
find_package(SFML COMPONENTS audio graphics network system window REQUIRED)
if(NOT SFML_FOUND)
	message(FATAL_ERROR "SFML is needed to build the project. Please install it correctly.")
endif()

include_directories(${SFML_INCLUDE_DIRS})

