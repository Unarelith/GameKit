set(SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/audio/AudioPlayer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/audio/Music.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/audio/Sound.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/core/ApplicationStateStack.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/ArgumentParser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/CoreApplication.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/Filesystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/GameClock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/core/Logger.cpp
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
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/Font.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/Image.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/RectangleShape.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/Sprite.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/SpriteAnimation.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/Text.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/TextInput.cpp
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

	PARENT_SCOPE)
