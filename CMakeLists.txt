cmake_minimum_required(VERSION 3.17)
project(Arcade)

set(CMAKE_CXX_STANDARD 20)

include_directories(sources)
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
        sources/Core/Runner/Runner.cpp
        sources/Core/Runner/Runner.hpp
        sources/Core/Library.hpp
        sources/Core/Library.cpp
        sources/Exceptions/InvalidLibraryException.hpp
        sources/Exceptions/InvalidArgumentException.hpp
)

target_link_libraries(arcade dl)