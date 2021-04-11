How to create a display Library
###############################################

To create a display module, you will need to create a shared library with 3 differents things.
    - An header
    - A getter of your Module
    - The implementation of your :term:`Display Module`

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

Here is the getHeader of the SFML's implementation for an example:

.. code-block:: c++

    extern "C" ModInfo getHeader()
    {
        ModInfo m;

        m.magicNumber = MagicNumber;
        m.name = "SFML";
        m.type = ModInfo::Modtype::GRAPHIC;
        return m;
    }

The getModule function
-----------------------

You have to implement the getModule function that should return the third's needed thing: a IDisplayModule implementation.

Definition in Module.hpp

.. code-block:: c++

    //! @brief Get the module class.
    //! @return A new instance of a IDisplayModule or IGameModule.
    extern "C" Arcade::IModule *getModule();

Here is the SFML implementation:

.. code-block:: c++

   extern "C" Arcade::IModule *getModule()
   {
      return new SFMLDisplay;
   }

IDisplayModule implementation
-------------------------------

And the last thing you need is a IDisplayModule implementation. Here is the IDIsplayModule's header:

.. code-block:: c++
    :linenos:

    /*
    ** EPITECH PROJECT, 2021
    ** Arcade
    ** File description:
    ** IDisplayLibrary
    */

    #pragma once

    #include "Common/Module.hpp"
    #include "Common/Drawables/Line.hpp"
    #include "Common/Drawables/Rectangle.hpp"
    #include "Common/Drawables/Circle.hpp"
    #include "Common/Drawables/Sprite.hpp"
    #include "Common/Drawables/Text.hpp"
    #include "Common/Events/Event.hpp"
    #include "Common/Sound.hpp"
    #include <list>
    #include <memory>

    namespace Arcade
    {
      //! @brief The interface of every display modules
      class IDisplayModule : public IModule
      {
      public:
        //! @brief Virtual destructor
        ~IDisplayModule() override = default;

        //! @brief Pull events (Keys, Clicks, Closes...)
        //! @return The list of events that occurred.
        virtual std::list<std::unique_ptr<Event>> pullEvents() = 0;

        //! @brief Draw a line.
        //! @param obj The line to draw.
        //! @return True if the line could be drawned. False otherwise.
        virtual bool draw(Drawables::Line &obj) = 0;

        //! @brief Draw a rectangle.
        //! @param obj The rectangle to draw.
        //! @return True if the rectangle could be drawned. False otherwise.
        virtual bool draw(Drawables::Rectangle &obj) = 0;

        //! @brief Draw a circle.
        //! @param obj The circle to draw.
        //! @return True if the circle could be drawned. False otherwise.
        virtual bool draw(Drawables::Circle &obj) = 0;

        //! @brief Draw a sprite.
        //! @param obj The sprite to draw.
        //! @return True if the sprite could be drawned. False otherwise.
        virtual bool draw(Drawables::Sprite &obj) = 0;

        //! @brief Draw a text.
        //! @param obj The text to draw.
        //! @return True if the text could be drawned. False otherwise.
        virtual bool draw(Drawables::Text &obj) = 0;

        //! @brief Refresh the screen, clear left-overs and draw requested objects.
        virtual bool refresh() = 0;

        //! @brief Load a resource
        //! @return Return true if the resource was successfully loaded. False otherwise
        virtual bool load(const std::string &type, const std::string &path) = 0;

        //! @brief Unload a resource
        virtual void unload(const std::string &type, const std::string &path) = 0;

        //! @brief Unload all resources loaded.
        virtual void unloadAll() = 0;

        //! @brief Play a sound
        virtual void playSound(Sound &sound) = 0;
      };
    }

Additional information
------------------------

You need to implement every method to make a display work. The draw functions are called every frame for each objects and should allow you to put objects on your internal buffer or on the screen and the refresh function is called after every draw to clear your buffer, update the screen with your internal buffer or any other things that you must do every frame.

The pullEvent method should return keyboard, mouse and close events that occurs from your display. Theses events are then handled by the core or the game depending on the type of event.

.. note::
    Refer to the Event page to see more

The load method allow you to load and cache resources that the game will use (3D objects, sprites, fonts, musics...) The most used types are: "font" and "sprite". The unloads methods allow you to clear your cache.

Sounds are handled by the playSound methods. Few games support them but this method should allow repeated and brief sounds.

Inherited from the IModule's interface, you also have a init and close methods witch allow you to initialize and destroy resources that you may need (an X window, a ncurses window...). There is also a shouldClose method witch allow you to tell the core to close itself gracefully.
