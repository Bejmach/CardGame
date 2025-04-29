cmake_minimum_required(VERSION 3.10)
project(CardGameClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#add_subdirectory(external/SDL2)
#add_subdirectory(external/SDL2_net)

#set(SDL2_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/external/SDL2/include)
#set(SDL2_NET_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/external/SDL2_net)

# Include SDL2 headers
#include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_NET_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/internal/include)

file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(CardGameClient ${PROJECT_SOURCES})

target_link_libraries(CardGameClient)
#SDL2 SDL2main SDL2_net
