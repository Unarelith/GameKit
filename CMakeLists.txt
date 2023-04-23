#------------------------------------------------------------------------------
# CMake configuration
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME gamekit)

project(${PROJECT_NAME})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(GK_BUILD_TESTS ON "Enable building tests if CxxTest is available")

#------------------------------------------------------------------------------
# Compiler flags
#------------------------------------------------------------------------------
set(DEBUG_GCC_FLAGS
	-g
	-Wall -Wextra -Wconversion
	-Wfatal-errors
	-DGK_DEBUG
)

set(RELEASE_GCC_FLAGS
	-O3
	-Wall -Wextra -Wconversion
	-Wfatal-errors
)

set(RELWITHDEB_GCC_FLAGS
	-g -O3
	-Wall -Wextra -Wconversion
	-Wfatal-errors
)

set(PUBLIC_GCC_FLAGS
	-D_USE_MATH_DEFINES
	-pedantic
	-Wno-variadic-macros
	-Wnon-virtual-dtor
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CLANG_FLAGS
		-Wno-sign-conversion
		-Wno-implicit-int-float-conversion
	)
endif()

set(CMAKE_CXX_STANDARD 17)

#------------------------------------------------------------------------------
# Setting default build type
#------------------------------------------------------------------------------
set(DEFAULT_BUILD_TYPE RelWithDebInfo)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
	set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)

	# Set the possible values of build type for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

#------------------------------------------------------------------------------
# Overwrite message function for clean output
#------------------------------------------------------------------------------
function(message)
    if (NOT MESSAGE_QUIET)
        _message(${ARGN})
    endif()
endfunction()

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
		execute_process(COMMAND ${GIT_EXECUTABLE} submodule sync --recursive WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
		execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			RESULT_VARIABLE GIT_SUBMOD_RESULT)
		if(NOT GIT_SUBMOD_RESULT EQUAL "0")
			message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
		endif()
	endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/tinyxml2/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(BUILD_STATIC_LIBS ON CACHE BOOL "")

#------------------------------------------------------------------------------
# - SDL2
#------------------------------------------------------------------------------
set(MESSAGE_QUIET ON)

add_subdirectory(external/SDL2)

set(SDL2IMAGE_INSTALL OFF CACHE BOOL "")

add_subdirectory(external/SDL2_image)

unset(MESSAGE_QUIET)

#------------------------------------------------------------------------------
# - GLEW
#------------------------------------------------------------------------------
set(glew-cmake_BUILD_STATIC ON CACHE BOOL "")
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "")
set(glew-cmake_BUILD_MULTI_CONTEXT OFF CACHE BOOL "")

add_subdirectory(external/glew)

#------------------------------------------------------------------------------
# - glm
#------------------------------------------------------------------------------
add_subdirectory(external/glm)

#------------------------------------------------------------------------------
# - tinyxml2
#------------------------------------------------------------------------------
add_subdirectory(external/tinyxml2)

#------------------------------------------------------------------------------
# Sources
#------------------------------------------------------------------------------
add_subdirectory(source)

#------------------------------------------------------------------------------
# Unit testing
#------------------------------------------------------------------------------
if(GK_BUILD_TESTS)
	find_package(CxxTest QUIET)

	if(CXXTEST_FOUND)
		include_directories(${CXXTEST_INCLUDE_DIRS})
		enable_testing()

		file(GLOB_RECURSE TEST_FILES tests/*.hpp)
		CXXTEST_ADD_TEST(${PROJECT_NAME}_tests unit-test.cpp ${TEST_FILES})
		target_link_libraries(${PROJECT_NAME}_tests ${PROJECT_NAME})
	else()
		message(WARNING "CxxTest not found!")
	endif()
endif()

