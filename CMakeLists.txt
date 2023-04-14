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


# Add executable target
add_executable(${PROJECT_NAME}
    src/Game.cpp
    src/mainwindow.ui
    src/mainwindow.cpp
    src/Room.cpp
    src/Item.cpp
    src/Command.cpp
    src/Parser.cpp
    src/CommandWords.cpp

)

# # Add source files
# target_sources(${PROJECT_NAME}
#     PRIVATE
       

# )

# Add include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        include
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

# Set output directory
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)