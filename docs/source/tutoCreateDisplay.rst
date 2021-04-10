How to create a display Library step by step
###############################################

To create a display module, you will need to create a shared library with 3 differents things.

The two first things are C style functions that will be used to determine the type of module you create and to start your module.

The first one is the get header. It should have this signature:
```extern "C" Arcade::ModInfo getHeader()```


It must return theses informations about your module:

 - it's name
 - it's type (a game or a display)
 - and a magic number (used to check if this module is for an arcade or not)

Here is the getHeader of the Pacman's game for an exemple:

 .. code-block:: c++
   :linenos:
    extern "C" Arcade::ModInfo getHeader()
    {
      Arcade::ModInfo info;
      info.name = "Pacman";
      info.type = Arcade::ModInfo::GAME;
      info.magicNumber = Arcade::MagicNumber;
      return info;
    }

You must also implement the getModule function that should return the third's needed thing: a IDisplayModule implementation. Here is the sfml implementation:

 .. code-block:: c++
   :linenos:
   extern "C" Arcade::IModule *getModule()
   {
      return new SFMLDisplay;
   }

And the last thing you need is a IDisplayModule implementation. Here is the IDIsplayModule's header:

  .. code-block:: c++
    :lineos:
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
        //! @brief Virtual destructror
        ~IDisplayModule() override = default;

        //! @brief Pull events (Keys, Clicks, Closes...)
        //! @return The list of events that occured.
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

You need to implement every methods to make a display work. The draw functions are called every frame for each objects and should allow you to put objects on your internal buffer or on the screen and the refresh function is called after every draw to clear your buffer, update the screen with your internal buffer or any other things that you must do every frame.

The pullEvent method should return keyboard, mouse and close events that occurs from your display. Theses events are then handled by the core or the game depending on the type of event.

The load method allow you to load and cache resources that the game will use (3D objects, sprites, fonts, musics...) The most used types are: "font" and "sprite". The unloads methods allow you to clear your cache.

Sounds are handled by the playSound methods. Few games support them but this method should allow repeated and brief sounds.

Inherited from the IModule's interface, you also have a init and close methods witch allow you to initialize and destroy resources that you may need (an X window, a ncurses window...). There is also a shouldClose method witch allow you to tell the core to close itself gracefully.
