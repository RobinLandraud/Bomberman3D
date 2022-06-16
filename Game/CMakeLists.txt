set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
FIND_PACKAGE(raylib 4.0.0 REQUIRED)

add_library(
    Game
    Bomb.cpp
    Bonuses.cpp
    Map.cpp
    Player.cpp
    Bot.cpp
    Game.cpp
    ACharacter.cpp
)

TARGET_LINK_LIBRARIES(Game raylib)
set_property(TARGET Game PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/Engine"
    "${CMAKE_SOURCE_DIR}/Utils"
    "${CMAKE_SOURCE_DIR}/Menu"
    "${CMAKE_SOURCE_DIR}/AScene"
    )