cmake_minimum_required(VERSION 3.12)
project(ForestGumpLite)

set(CMAKE_CXX_STANDARD 11)

add_executable(ForestGumpLite src/main.cpp src/actors/actor.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
# Detect and add SFML
set(SFML_DIR "/usr/share/SFML")

find_package(SFML 2.4 REQUIRED COMPONENTS audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()