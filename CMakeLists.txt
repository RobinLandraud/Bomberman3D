CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
project("indie" VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(
    ${PROJECT_NAME}
    main.cpp
)


add_subdirectory(Error)
add_subdirectory(AScene)
add_subdirectory(Game)
add_subdirectory(Menu)
add_subdirectory(Utils)
add_subdirectory(Core)
add_subdirectory(Engine)

target_link_libraries(${PROJECT_NAME} AScene)
target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} Error)
target_link_libraries(${PROJECT_NAME} Game)
target_link_libraries(${PROJECT_NAME} Utils)
target_link_libraries(${PROJECT_NAME} Menu)
target_link_libraries(${PROJECT_NAME} Core)
target_link_libraries(${PROJECT_NAME} Engine)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/Engine"
    "${CMAKE_SOURCE_DIR}/AScene"
    "${CMAKE_SOURCE_DIR}/Event"
    "${CMAKE_SOURCE_DIR}/Game"
    "${CMAKE_SOURCE_DIR}/Utils"
    "${CMAKE_SOURCE_DIR}/Menu"
    "${CMAKE_SOURCE_DIR}/Core"
)