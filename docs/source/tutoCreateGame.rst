How to create a game Library
##########################################

To create a game module, you will need to create a shared library with 3 differents things.
    - An header
    - A getter of your Module
    - The implementation of your :term:`Game Module`

The getHeader function
------------------------

The two first things are C style functions that will be used by the arcade :term:`Core` to determine the type of your module.

The first one is the get header. It should have this signature:
```extern "C" Arcade::ModInfo getHeader()```


It must return theses informations about your module:

 - it's name
 - it's type (a game or a display)
 - and a magic number (used to check if this module is compatible with our arcade)

Definition in Module.hpp

.. code-block:: c++

    //! @brief Get the library's header.
    //! @info Used to verify the integrity of the lib.
    extern "C" Arcade::ModInfo getHeader();

Here is the getHeader of the Pacman's game for an example:

.. code-block:: c++

    extern "C" Arcade::ModInfo getHeader()
    {
      Arcade::ModInfo info;
      info.name = "Pacman";
      info.type = Arcade::ModInfo::GAME;
      info.magicNumber = Arcade::MagicNumber;
      return info;
    }

The getModule function
-----------------------

You have to implement the getModule function that should return the third's needed thing: a IGameModule implementation.

Definition in Module.hpp

.. code-block:: c++

    //! @brief Get the module class.
    //! @return A new instance of a IDisplayModule or IGameModule.
    extern "C" Arcade::IModule *getModule();

Here is the pacman implementation:

.. code-block:: c++

   extern "C" Arcade::IModule *getModule()
   {
      return new Pacman;
   }

IGameModule implementation
-------------------------------

And the last thing you need is a IGameModule implementation. Here is the IGameModule :term:`Interface`

.. code-block:: c++
    :linenos:

    /*
    ** EPITECH PROJECT, 2021
    ** Arcade
    ** File description:
    ** IGameLibrary
    */

    #pragma once

    #include "Common/ModInfo.hpp"
    #include "Common/Drawables/ADrawable.hpp"
    #include "Common/Module.hpp"
    #include "Common/Events/Event.hpp"
    #include "Common/Sound.hpp"
    #include <vector>
    #include <memory>
    #include <string>

    namespace Arcade
    {
      //! @brief The interface of all games.
      class IGameModule : public IModule
      {
      public:
        //! @brief Virtual destructor
        ~IGameModule() override = default;

        //! @brief Get resources to preload.
        //! @info Only called once.
        //! @return A vector of tupple of (type of resource, path of the resource).
        virtual const std::vector<std::pair<std::string, std::string>> &getResources() const = 0;

        //! @brief Return a list of drawables to display.
        //! @return The list of objects
        virtual const std::vector<std::unique_ptr<Drawables::ADrawable>> &getDrawables() = 0;

        //! @brief Return a list of sounds to make.
        //! @return The list of sounds
        virtual const std::vector<Sound> &getSounds() = 0;

        //! @brief Advance the game of x seconds
        //! @param tick The number of ticks that occured since the last call.
        virtual void addTicks(unsigned tick) = 0;

        //! @brief Restart the game.
        virtual void restart() = 0;

        //! @brief Handle one event (A key press, a click, a close event...)
        //! @param event The event to handle.
        virtual void handleEvent(Event &event) = 0;

        //! @brief Get the score (used for saving/displaying)
        virtual unsigned long getScore() = 0;
      };
    }


Additional information
------------------------

The getResource function is called at the start of the game and when a new display module is loaded. It should return the complete list of resources that displays might need (sprites, 3D objects, musics files, fonts...).

.. warning::
     Since the getResource function is only called at the start of the game and at the moment of switching the :term:`Display Module`
     If you specify a resource later on without returning it first, it might not be displayed.

The getDrawables and getSounds are called every frame. The getDrawable should return every Drawables objects that need to be displayed. While the getSounds function should return new sounds to play (you can loop sounds or stop every other sounds if you want).

.. warning::
    The tick parameter is in **microseconds** not in milliseconds which is a common mistake

The addTicks should be used to update your game. The tick parameter is the number of microseconds since the last call and is used to prevents differences between differents display refresh rate (the SDL is faster than the ncurses for example).

The handleEvent allow you to do things on mouse clicks or key events.

.. note::
    Refer to the Event page to see more

The getScore is used to save the user's best score and display it on the menu.

The restart function allow the user to restart the game from scratch without having to close the game.
