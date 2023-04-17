# Set minimum CMake version
cmake_minimum_required(VERSION 3.16)

# Set project name and version
project(Game 
        VERSION 1.0.0
        DESCRIPTION "Game"
        LANGUAGES CXX
        )

# Set the vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

# Set the source directories for each component
set(MODEL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/model")
set(GUI_VIEW_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/view/gui")
set(CLI_VIEW_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/view/cli")
set(CONTROLLER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/controller")

# Add the source files for the model
add_library(model
        ${MODEL_DIR}/Room.cpp
        ${MODEL_DIR}/Item.cpp
        ${MODEL_DIR}/Command.cpp
        ${MODEL_DIR}/Parser.cpp
        ${MODEL_DIR}/CommandWords.cpp
)

include_directories(${MODEL_DIR})

# Add the source files for the GUI view
set(GUI_VIEW_SRCS
        ${GUI_VIEW_DIR}/GameGUI.cpp
        ${GUI_VIEW_DIR}/GameWindow.cpp
        ${GUI_VIEW_DIR}/GameWindow.ui
)

qt_add_executable(gui_view ${GUI_VIEW_SRCS})
target_link_libraries(gui_view PRIVATE model Qt6::Widgets)

# Add the source files for the CLI view
add_executable(cli_view
        ${CLI_VIEW_DIR}/GameCLI.cpp
)

include_directories(${CLI_VIEW_DIR})

# Add the source files for the controller
add_executable(controller
        ${CONTROLLER_DIR}/GameController.cpp
)

# add all headers to the project
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

include_directories(${CONTROLLER_DIR})

# Link the targets with necessary libraries
target_link_libraries(cli_view PRIVATE model)
target_link_libraries(controller PRIVATE model)

set_target_properties(gui_view PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
