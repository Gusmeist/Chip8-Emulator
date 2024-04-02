cmake_minimum_required(VERSION 3.29.0-rc3)
project(chip8emu VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${chip8emu_SOURCE_DIR}/cmake)

find_package(SDL2 CONFIG REQUIRED)

include_directories(chip8emu ${SDL2_INCLUDE_DIR} ${chip8emu_SOURCE_DIR}/src/Core)
link_directories(chip8emu ${SDL2_LIBDIR})

include(CTest)
enable_testing()

add_executable(chip8emu 
    ${chip8emu_SOURCE_DIR}/src/Core/main.cpp
    ${chip8emu_SOURCE_DIR}/src/Core/cpu.h
    ${chip8emu_SOURCE_DIR}/src/Core/cpu.cpp
    ${chip8emu_SOURCE_DIR}/src/Core/display.h
    ${chip8emu_SOURCE_DIR}/src/Core/display.cpp
    ${chip8emu_SOURCE_DIR}/src/Core/memory.h
    ${chip8emu_SOURCE_DIR}/src/Core/memory.cpp
    ${chip8emu_SOURCE_DIR}/src/Core/mystack.h
    ${chip8emu_SOURCE_DIR}/src/Core/mystack.cpp
    ${chip8emu_SOURCE_DIR}/src/Core/sdl_interface.h
    ${chip8emu_SOURCE_DIR}/src/Core/sdl_interface.cpp
    ${chip8emu_SOURCE_DIR}/src/Core/time_keeper.h
    ${chip8emu_SOURCE_DIR}/src/Core/time_keeper.cpp
)
target_link_libraries(chip8emu ${SDL2_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)