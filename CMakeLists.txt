#------------------------------------------------------------------------------
# CMake configuration
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.1)

project(gamekit VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#------------------------------------------------------------------------------
# Get source files
#------------------------------------------------------------------------------
file(GLOB_RECURSE SOURCE_FILES source/*.cpp external/*.cpp)

include_directories(include/)

#------------------------------------------------------------------------------
# Add executables
#------------------------------------------------------------------------------
add_library(${CMAKE_PROJECT_NAME} STATIC
            ${SOURCE_FILES})

#------------------------------------------------------------------------------
# Setup install rule
#------------------------------------------------------------------------------
include(GNUInstallDirs)

install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY include/gk DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#------------------------------------------------------------------------------
# Compiler flags
#------------------------------------------------------------------------------
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -g)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Wfatal-errors)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wno-variadic-macros)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -static-libstdc++)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -DDEBUG_ENABLED -DDEBUG_COLOR)
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_14)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc")
endif()

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
# - SDL2, SDL2_image, SDL2_mixer, SDL2_ttf
#------------------------------------------------------------------------------
include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2MIXER REQUIRED SDL2_mixer)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf)

if(NOT SDL2_FOUND)
	message(FATAL_ERROR "SDL2 not found!")
endif(NOT SDL2_FOUND)

if(NOT SDL2IMAGE_FOUND)
	message(FATAL_ERROR "SDL2_image not found!")
endif(NOT SDL2IMAGE_FOUND)

if(NOT SDL2MIXER_FOUND)
	message(FATAL_ERROR "SDL2_mixer not found!")
endif(NOT SDL2MIXER_FOUND)

if(NOT SDL2TTF_FOUND)
	message(FATAL_ERROR "SDL2_mixer not found!")
endif(NOT SDL2TTF_FOUND)

include_directories(${SDL2_INCLUDE_DIRS}
                    ${SDL2IMAGE_INCLUDE_DIRS}
                    ${SDL2MIXER_INCLUDE_DIRS}
                    ${SDL2TTF_INCLUDE_DIRS})

