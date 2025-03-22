cmake_minimum_required(VERSION 3.10)
project(CardGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external/SDL2)
add_subdirectory(external/SDL2_net)

set(SDL2_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/external/SDL2/include)
set(SDL2_NET_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/external/SDL2_net)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_NET_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/internal/include)

file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/internal/src/*.cpp")

add_executable(CardGame ${PROJECT_SOURCES}
        internal/include/RequestTranslator.h)

target_link_libraries(CardGame SDL2 SDL2main SDL2_net)
