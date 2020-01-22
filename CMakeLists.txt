#------------------------------------------------------------------------------
# CMake configuration
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.1)

project(gamekit VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" "${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2")

add_subdirectory(source)

if (WIN32)
	set(WIN_LIBRARIES_PATH "C:/Libraries")
endif ()

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
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -DDEBUG_ENABLED -DDEBUG_COLOR)

if(NOT MSVC)
	target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Wfatal-errors)
	target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -Wno-variadic-macros)
endif()

set(CMAKE_CXX_STANDARD 14)

# target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -std=c++14)
# target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_14)

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
# - SDL2, SDL2_image, SDL2_mixer, SDL2_ttf
#------------------------------------------------------------------------------
if (WIN32)
	set(SDL2_PATH       ${WIN_LIBRARIES_PATH}/SDL2/i686-w64-mingw32       CACHE BOOL "" FORCE)
	set(SDL2_IMAGE_PATH ${WIN_LIBRARIES_PATH}/SDL2_image/i686-w64-mingw32 CACHE BOOL "" FORCE)
	set(SDL2_MIXER_PATH ${WIN_LIBRARIES_PATH}/SDL2_mixer/i686-w64-mingw32 CACHE BOOL "" FORCE)
	set(SDL2_TTF_PATH   ${WIN_LIBRARIES_PATH}/SDL2_ttf/i686-w64-mingw32   CACHE BOOL "" FORCE)
elseif (MSVC)
	set(SDL2_PATH       ${WIN_LIBRARIES_PATH}/SDL2       CACHE BOOL "" FORCE)
	set(SDL2_IMAGE_PATH ${WIN_LIBRARIES_PATH}/SDL2_image CACHE BOOL "" FORCE)
	set(SDL2_MIXER_PATH ${WIN_LIBRARIES_PATH}/SDL2_mixer CACHE BOOL "" FORCE)
	set(SDL2_TTF_PATH   ${WIN_LIBRARIES_PATH}/SDL2_ttf   CACHE BOOL "" FORCE)
endif ()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

if(NOT SDL2_FOUND)
	message(FATAL_ERROR "SDL2 not found!")
endif(NOT SDL2_FOUND)

if(NOT SDL2_IMAGE_FOUND)
	message(FATAL_ERROR "SDL2_image not found!")
endif(NOT SDL2_IMAGE_FOUND)

if(NOT SDL2_MIXER_FOUND)
	message(FATAL_ERROR "SDL2_mixer not found!")
endif(NOT SDL2_MIXER_FOUND)

if(NOT SDL2_TTF_FOUND)
	message(FATAL_ERROR "SDL2_ttf not found!")
endif(NOT SDL2_TTF_FOUND)

include_directories(${SDL2_INCLUDE_DIRS}
                    ${SDL2_IMAGE_INCLUDE_DIRS}
                    ${SDL2_MIXER_INCLUDE_DIRS}
                    ${SDL2_TTF_INCLUDE_DIRS})

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
