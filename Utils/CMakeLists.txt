add_library(
    Utils
    Clock.cpp
)

set_property(TARGET Utils PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})