cmake_minimum_required(VERSION 3.12)
project(ForestGumpLite)

set(CMAKE_CXX_STANDARD 11)

add_executable(ForestGumpLite src/game/main.cpp src/game/actors/actor.cpp src/game/actors/obstacle.cpp src/game/actors/obstacle.h src/game/map/mapManager.cpp src/game/map/mapManager.h src/game/gameManager.cpp src/game/gameManager.h src/game/actors/player.cpp src/game/actors/player.h src/util/serializer.cpp src/util/serializer.h src/game/scenes/scene.cpp src/game/scenes/scene.h src/game/scenes/sceneMainMenu.cpp src/game/scenes/sceneMainMenu.h src/game/scenes/sceneGame.cpp src/game/scenes/sceneGame.h)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
# Detect and add SFML
set(SFML_DIR "/usr/share/SFML")

find_package(SFML 2.4 REQUIRED COMPONENTS audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()