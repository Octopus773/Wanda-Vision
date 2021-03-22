cmake_minimum_required(VERSION 3.17)
project(Arcade)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

include_directories(sources/Common)

add_executable(arcade
        main.cpp
        sources/Common/GameObjects/CircleObject.hpp
        sources/Common/GameObjects/LineObject.hpp
        sources/Common/GameObjects/RectangleObject.hpp
        sources/Common/GameObjects/SpriteObject.hpp
        sources/Common/Events/ClickEvent.hpp
        sources/Common/Events/CloseEvent.hpp
        sources/Common/Events/KeyEvent.hpp
        sources/Common/Event.hpp
        sources/Common/GameObject.hpp
        sources/Common/IDisplayModule.hpp
        sources/Common/IGameModule.hpp
        sources/Common/ModInfo.hpp
        sources/Common/Module.hpp
        )

add_library(SDL2Display
        SHARED
        sources/DisplayModules/SDLDisplay.cpp
        sources/DisplayModules/SDLDisplay.hpp
        )

target_link_libraries(SDL2Display SDL2)