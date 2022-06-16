set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
FIND_PACKAGE(raylib 4.0.0 REQUIRED)
add_library(
    AScene
    AScene.cpp
)

TARGET_LINK_LIBRARIES(AScene raylib)
set_property(TARGET AScene PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(AScene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/Core"
    "${CMAKE_SOURCE_DIR}/Engine"
    "${CMAKE_SOURCE_DIR}/Menu"
)