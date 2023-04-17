add_library(logic STATIC
    Game.cpp
    Room.cpp
    Item.cpp
    Command.cpp
    Parser.cpp
    CommandWords.cpp
)
target_link_libraries(logic PRIVATE Qt6::Core)
target_include_directories(logic INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})