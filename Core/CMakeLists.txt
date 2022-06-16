set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
FIND_PACKAGE(raylib 4.0.0 REQUIRED)

add_library(
    Core
    Core.cpp
)

TARGET_LINK_LIBRARIES(Core raylib)
set_property(TARGET Core PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/Menu"
    "${CMAKE_SOURCE_DIR}/Game"
    "${CMAKE_SOURCE_DIR}/Engine"
    "${CMAKE_SOURCE_DIR}/Utils"
    "${CMAKE_SOURCE_DIR}/AScene"
    )