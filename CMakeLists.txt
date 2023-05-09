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

# set(CMAKE_EXE_LINKER_FLAGS_INIT "-fuse-ld=lld")
# set(CMAKE_MODULE_LINKER_FLAGS_INIT "-fuse-ld=lld")
# set(CMAKE_SHARED_LINKER_FLAGS_INIT "-fuse-ld=lld")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

# Set the source directories for each component
set(MODEL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/model")
set(VIEW_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/view")
set(CONTROLLER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/controller")

# Add the source files for the model
add_library(model
        ${MODEL_DIR}/Room.cpp
        ${MODEL_DIR}/Item.cpp
        ${MODEL_DIR}/Character.cpp
        ${MODEL_DIR}/GameState.cpp
        ${MODEL_DIR}/GameModel.cpp
        
)

target_include_directories(model PUBLIC ${MODEL_DIR})

# Add the source files for the GUI view
set(GUI_VIEW_DIR "${VIEW_DIR}/gui")
set(GUI_VIEW_SRCS
        ${GUI_VIEW_DIR}/MainWindow.cpp
        ${GUI_VIEW_DIR}/MainWindow.ui
)
add_library(gui_view ${GUI_VIEW_SRCS})
target_include_directories(gui_view PUBLIC ${GUI_VIEW_DIR})
target_link_libraries(gui_view PRIVATE model Qt6::Widgets)



# Add the source files for the controller
add_library(controller 
        ${CONTROLLER_DIR}/GameController.cpp
        ${CONTROLLER_DIR}/Command.cpp
)
target_include_directories(controller PUBLIC ${CONTROLLER_DIR})


# Link the targets with necessary libraries
target_link_libraries(gui_view PUBLIC model)
target_link_libraries(controller PUBLIC model Qt6::Widgets)
target_link_libraries(model PUBLIC Qt6::Widgets)


# Create the executable target
add_executable(game ${CONTROLLER_DIR}/GameController.cpp)
target_link_libraries(game PUBLIC controller model gui_view)




set_target_properties(game PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
