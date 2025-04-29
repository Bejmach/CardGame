cmake_minimum_required(VERSION 3.16)

project(MakaoGame VERSION 1.0 LANGUAGES CXX)

# Enable automatic Qt features
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt packages
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui)

# Main application sources
set(APP_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/GameController.cpp
)

# UI files
set(UI_FILES
    src/mainwindow.ui
)

# Backend sources
set(BACKEND_SOURCES
    src/ClientBase.cpp
    src/ClientPlayer.cpp
    src/ClientBot.cpp
    src/GameMaster.cpp
    src/Deck.cpp
    src/Card.cpp
    src/CardHolder.cpp
    src/Validator.cpp
    src/MakaoValidator.cpp
    src/SpecialRules.cpp
    src/MakaoRules.cpp
    src/Logger.cpp
    src/CardTranslator.cpp
    src/RequestTranslator.cpp
    src/StringOperations.cpp
    src/CardTypes.cpp
)

# Resource files
set(RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/cards/resources.qrc
)

# Create executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MakaoGame
        MANUAL_FINALIZATION
        ${APP_SOURCES}
        ${UI_FILES}
        ${BACKEND_SOURCES}
        ${RESOURCES}
    )
else()
    add_executable(MakaoGame
        ${APP_SOURCES}
        ${UI_FILES}
        ${BACKEND_SOURCES}
        ${RESOURCES}
    )
endif()

# Target properties
set_target_properties(MakaoGame PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Link libraries
target_link_libraries(MakaoGame PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
)

# Install rules
include(GNUInstallDirs)
install(TARGETS MakaoGame
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Copy assets
add_custom_command(TARGET MakaoGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:MakaoGame>/cards
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets/cards
        $<TARGET_FILE_DIR:MakaoGame>/cards
)

# Finalize for Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MakaoGame)
endif()
