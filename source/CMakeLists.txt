set(SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/core/ApplicationStateStack.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/ArgumentParser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/CoreApplication.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/Filesystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/GameClock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/KeyboardUtils.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/Mouse.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/Timer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/XMLFile.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/input/GamePad.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/input/InputHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/input/KeyboardHandler.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/graphics/Image.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/Sprite.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/SpriteAnimation.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/Tilemap.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/Tileset.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/tilemap/TilemapAnimator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/tilemap/TilemapRenderer.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/resource/AudioPlayer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/resource/ResourceHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/resource/TextureLoader.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/scene/CollisionHelper.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene/Scene.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene/controller/BehaviourController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene/controller/LifetimeController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene/controller/MovementController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene/movement/GamePadMovement.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene/view/HitboxView.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/scene/view/SpriteView.cpp

	PARENT_SCOPE)
