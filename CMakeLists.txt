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
        sources/Games/Menu/Menu.cpp
        sources/Games/Menu/Menu.hpp
)
target_link_libraries(arcade dl)

add_executable(unit_tests
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
        sources/Games/Menu/Menu.cpp
        sources/Games/Menu/Menu.hpp
        tests/Library.cpp
)
target_link_libraries(unit_tests dl)
target_link_libraries(unit_tests criterion -lgcov)
target_compile_options(unit_tests PUBLIC -fprofile-arcs -ftest-coverage)

add_library(arcade_sdl2 SHARED
        sources/DisplayModules/SDL/SDLDisplay.cpp
        sources/DisplayModules/SDL/SDLDisplay.hpp
)
set_target_properties(arcade_sdl2 PROPERTIES PREFIX "")
target_link_libraries(arcade_sdl2 SDL2 SDL2_image SDL2_ttf SDL2_mixer SDL2_gfx)

add_library(arcade_ncurses SHARED
        sources/DisplayModules/Ncurses/NcursesDisplay.hpp
        sources/DisplayModules/Ncurses/NcursesDisplay.cpp
)
set_target_properties(arcade_ncurses PROPERTIES PREFIX "")
target_link_libraries(arcade_ncurses ncurses)

add_library(arcade_qix SHARED
        sources/Games/Qix/Qix.cpp
        sources/Games/Qix/Qix.hpp
)
set_target_properties(arcade_qix PROPERTIES PREFIX "")

add_library(arcade_pacman SHARED
        sources/Games/Pacman/Pacman.cpp
        sources/Games/Pacman/Pacman.hpp
        sources/Games/Pacman/Exceptions/WrongMapChar.hpp
        sources/Games/Pacman/Exceptions/WrongMapChar.hpp
)
set_target_properties(arcade_pacman PROPERTIES PREFIX "")

add_library(arcade_sfml SHARED
        sources/DisplayModules/SFML/SFMLDisplay.cpp
        sources/DisplayModules/SFML/SFMLDisplay.hpp
        sources/DisplayModules/SFML/Exceptions/ResourceCreationFailure.hpp
)
set_target_properties(arcade_sfml PROPERTIES PREFIX "")
target_link_libraries(arcade_sfml sfml-graphics sfml-window sfml-system sfml-audio)
