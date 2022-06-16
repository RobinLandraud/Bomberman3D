set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
FIND_PACKAGE(raylib 4.0.0 REQUIRED)
add_library(
    Menu
    AScene2D.cpp
    PlayerBox.cpp
    Settings.cpp
)

TARGET_LINK_LIBRARIES(Menu raylib)
set_property(TARGET Menu PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(Menu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/Core"
    "${CMAKE_SOURCE_DIR}/Engine"
    "${CMAKE_SOURCE_DIR}/AScene"
)