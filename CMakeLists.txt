cmake_minimum_required(VERSION 3.17)
project(Arcade)

set(CMAKE_CXX_STANDARD 20)

include_directories(sources)

add_executable(arcade
        main.cpp
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