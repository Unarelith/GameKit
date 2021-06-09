#------------------------------------------------------------------------------
# Add source files
#------------------------------------------------------------------------------
set(SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/core/ApplicationStateStack.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/ArgumentParser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/CoreApplication.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/Filesystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/GameClock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/ISerializable.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/Logger.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/LoggerHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/LoggerUtils.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/Mouse.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/SDLLoader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/Timer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/Utils.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/Window.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/XMLFile.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/input/GamePad.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/input/InputHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/input/KeyboardHandler.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/gl/Camera.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gl/GLCheck.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gl/RenderTarget.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gl/Shader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gl/Texture.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gl/Transform.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gl/Transformable.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gl/VertexBuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gl/View.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/graphics/BoxShape.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/Color.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/Image.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/RectangleShape.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/Sprite.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/SpriteAnimation.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/TiledImage.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/Tilemap.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/Tileset.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/tilemap/TilemapAnimator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/tilemap/TilemapRenderer.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/resource/ResourceHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/resource/TextureLoader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/resource/TilemapLoader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/resource/TilesetLoader.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/scene/CollisionHelper.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene/Scene.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene/controller/BehaviourController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene/controller/LifetimeController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene/controller/MovementController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene/movement/GamePadMovement.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene/view/HitboxView.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene/view/SpriteView.cpp
)

#------------------------------------------------------------------------------
# Add executables
#------------------------------------------------------------------------------
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

add_dependencies(${PROJECT_NAME}
	SDL2_image
	SDL2-static
	SDL2main
	tinyxml2
	libglew_static
	glm_static
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/../external
)

target_link_libraries(${PROJECT_NAME} PUBLIC
	SDL2_image
	SDL2-static
	SDL2main
	tinyxml2
	libglew_static
	glm_static
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
if(NOT MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_GCC_FLAGS}>")
	target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_GCC_FLAGS}>")
	target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELWITHDEBINFO>:${RELWITHDEB_GCC_FLAGS}>")
	target_compile_options(${PROJECT_NAME} PRIVATE ${CLANG_FLAGS})

	target_compile_options(${PROJECT_NAME} PUBLIC ${PUBLIC_GCC_FLAGS})
endif()

# target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

# target_compile_options(${PROJECT_NAME} PRIVATE -pg)
# target_link_options(${PROJECT_NAME} PRIVATE -pg)

