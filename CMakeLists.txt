cmake_minimum_required(VERSION 3.10)
project(CardGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect platform
if(MSVC)
    set(PLATFORM "VCode")
elseif(MINGW)
    set(PLATFORM "MinGw")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/external/${PLATFORM}/SDL2/cmake/")

# Adjust the path to your SDL2 development release
set(SDL2_DIR "external/SDL2/x86_64-mingw")

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_NET_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/internal/include)

file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/internal/src/*.cpp")

# Include the SDL2 headers
# include_directories(${SDL2_DIR}/include)

# Link against the SDL2 library
 add_executable(CardGame ${PROJECT_SOURCES})

# Find and link SDL2
# find_library(SDL2_LIBRARY NAMES SDL2 PATHS ${CMAKE_SOURCE_DIR}/${SDL2_DIR}/lib)
# find_library(SDL2MAIN_LIBRARY NAMES SDL2main PATHS ${CMAKE_SOURCE_DIR}/${SDL2_DIR}/lib)
# find_library(SDL2_NET_LIBRARY NAMES SDL2_net PATHS ${CMAKE_SOURCE_DIR}/${SDL2_DIR}/lib)

# if(NOT SDL2_LIBRARY OR NOT SDL2MAIN_LIBRARY OR NOT SDL2_NET_LIBRARY)
    # message(FATAL_ERROR "SDL2 libraries not found!")
# endif()

target_link_libraries(CardGame ${SDL2_LIBRARIES} ${SDL2_NET_LIBRARIES})

# Copy SDL2.dll to the build directory
# add_custom_command(TARGET SDLTest POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/${SDL2_DIR}/bin/SDL2.dll ${CMAKE_BINARY_DIR}
# 	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/${SDL2_DIR}/bin/SDL2_net.dll ${CMAKE_BINARY_DIR}
# )
