#------------------------------------------------------------------------------
# CMake configuration
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME gamekit)

project(${PROJECT_NAME})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTS ON "Enable building tests if CxxTest is available")

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

set(PNG_TESTS OFF CACHE BOOL "")
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
if(BUILD_TESTS)
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

