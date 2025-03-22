cmake_minimum_required(VERSION 3.15)
project(CardGame)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find libraries

# Find SDL3
find_package(SDL3 REQUIRED)
# Find SDL2_net
find_package(SDL2_net REQUIRED)

# Source files
set(SOURCES     src/Cards/Card.cpp
    src/Cards/CardHolder.cpp
    src/Cards/CardTranslator.cpp
    src/Cards/CardTypes.cpp
    src/Cards/Deck.cpp
    src/Clients/ClientBase.cpp
    src/Clients/ClientBot.cpp
    src/Clients/ClientPlayer.cpp
    src/main.cpp
    src/Other/Logger.cpp
    src/Other/StringOperations.cpp
    src/Rules/GameMaster.cpp
    src/Rules/MakaoRules.cpp
    src/Rules/MakaoValidator.cpp
    src/Rules/SpecialRules.cpp
    src/Rules/Validator.cpp
    src/Server/Server.cpp
        src/Translator/RequestTranslator.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES}
        src/Translator/RequestTranslator.cpp
)

# Include directories
include_directories(
    src/Cards
    src/Clients
    src/Other
    src/Rules
    src/Server)

# Ling against
target_link_libraries(${PROJECT_NAME}  SDL3::SDL3 SDL2_net::SDL2_net)


