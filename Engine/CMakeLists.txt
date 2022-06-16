set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
FIND_PACKAGE(raylib 4.0.0 REQUIRED)

add_library(
    Engine
    Engine.cpp
    AudioEngine.cpp
    Model3D.cpp
    Button.cpp
    Event.cpp
)

TARGET_LINK_LIBRARIES(Engine raylib)
set_property(TARGET Engine PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/Menu"
)