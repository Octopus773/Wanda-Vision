cmake_minimum_required(VERSION 3.17)
project(Arcade)

set(CMAKE_CXX_STANDARD 20)

include_directories(sources)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_executable(arcade
        sources/main.cpp
        sources/Common/Drawables/Circle.hpp
        sources/Common/Drawables/Line.hpp
        sources/Common/Drawables/Rectangle.hpp
        sources/Common/Drawables/Sprite.hpp
        sources/Common/Events/MouseClickEvent.hpp
        sources/Common/Events/MouseMoveEvent.hpp
        sources/Common/Events/KeyBoardEvent.hpp
        sources/Common/Events/Event.hpp
        sources/Common/Drawables/ADrawable.hpp
        sources/Common/IDisplayModule.hpp
        sources/Common/IGameModule.hpp
        sources/Common/ModInfo.hpp
        sources/Common/Module.hpp
        sources/Core/Runner/Runner.cpp
        sources/Core/Runner/Runner.hpp
        sources/Core/Library.hpp
        sources/Core/Library.cpp
        sources/Exceptions/InvalidLibraryException.hpp
        sources/Exceptions/InvalidArgumentException.hpp
)
target_link_libraries(arcade dl)

add_library(arcade_sdl2 SHARED
        sources/DisplayModules/SDLDisplay.cpp
        sources/DisplayModules/SDLDisplay.hpp
)
set_target_properties(arcade_sdl2 PROPERTIES PREFIX "")
target_link_libraries(arcade_sdl2 SDL2 SDL2_image SDL2_ttf SDL2_mixer SDL2_gfx)

add_library(arcade_qix SHARED
        sources/Games/Qix/Qix.cpp
        sources/Games/Qix/Qix.hpp
)
set_target_properties(arcade_qix PROPERTIES PREFIX "")

add_library(arcade_pacman SHARED
        sources/Games/Pacman/Pacman.cpp
        sources/Games/Pacman/Pacman.hpp
        sources/Games/Pacman/Exceptions/WrongMapChar.hpp)
set_target_properties(arcade_pacman PROPERTIES PREFIX "")