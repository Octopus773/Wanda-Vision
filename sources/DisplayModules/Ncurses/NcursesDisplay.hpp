//
// Created by cbihan on 3/22/21.
//

#pragma once

#include <string>
#include "Common/IDisplayModule.hpp"
#include "Common/Events/MouseClickEvent.hpp"
#include "Common/Events/KeyBoardEvent.hpp"
#include "Common/Events/MouseMoveEvent.hpp"
#include "Common/Events/Event.hpp"
#include <map>
#include <vector>
#include <ncurses.h>

namespace Arcade
{
	//! @brief Implementation of the ncurses Graphic Library
	class NcursesDisplay : public IDisplayModule
	{
	private:
		//! @brief When true the caller should close this instance
		bool _shouldClose = true;
		//! @brief A list of the keys that are currently hold
		//! @info keys are inserted in the list when an event keyDown as occurred and pop out when a keyUp occurred
		std::vector<Events::KeyboardEvent::KeyCode> _keysHolded;

		//! @brief The width of the window
		int _width;
		//! @brief The height of the window
		int _height;

		//! @brief Percent to position (X)
		//! @param x Position in percentage.
		int _getPosX(int x) const;
		//! @brief Percent to position (Y)
		//! @param y Position in percentage.
		int _getPosY(int y) const;

		//! @brief Get a keycode from a getch response
		Events::KeyboardEvent::KeyCode _getStdKey(unsigned int key) const;
		//! @brief Set the output to the object's color.
		void _setColor(Drawables::ADrawable &obj, bool fullblock = false) const;
	public:
		//! @brief Colors available.
		static constexpr std::array<std::array<int, 4>, 8> colors = {{
           {0, 0, 0, COLOR_BLACK},
           {255, 0, 0, COLOR_RED},
           {0, 255, 0, COLOR_GREEN},
           {0, 0, 255, COLOR_BLUE},
           {255, 255, 0, COLOR_YELLOW},
           {255, 0, 255, COLOR_MAGENTA},
           {0, 255, 255, COLOR_CYAN},
           {255, 255, 255, COLOR_WHITE}
       }};

		//! @brief Default constructor
		//! @warning In order to properly use this class you must call the init member function
		NcursesDisplay() = default;
		//! @brief Default copy constructor.
		//! @warning You must call the close member function before the destructor if you called the init member function
		~NcursesDisplay() override =  default;
		//! @brief Default copy constructor.
		explicit NcursesDisplay(const NcursesDisplay &) = default;
		//! @brief Default  assignment operator
		NcursesDisplay &operator=(const NcursesDisplay &) = default;

		//! @brief Initialize this library. (Create windows & so on)
		//! @return True if the initialization was successful. False otherwise.
		bool init() override;

		//! @brief Allow to say to the library to shutdown and free it's content
		//! @return True if the shutdown was successful. False otherwise.
		bool close() override;

		//! @brief Should this module be closed?
		//! @return True if this module should be closed. False otherwise.
		bool shouldClose() override;

		//! @brief Pull events (Keys, Clicks, Closes...)
		//! @return The list of events that occured.
		std::list<std::unique_ptr<Event>> pullEvents() override;

		//! @brief Draw a line.
		//! @param obj The line to draw.
		//! @return True if the text could be drawned. False otherwise.
		bool draw(Drawables::Line &obj) override;

		//! @brief Draw a rectangle.
		//! @param obj The rectangle to draw.
		//! @return True if the draw was successful. False otherwise.
		bool draw(Drawables::Rectangle &obj) override;

		//! @brief Draw a circle.
		//! @param obj The circle to draw.
		//! @return True if the draw was successful. False otherwise.
		bool draw(Drawables::Circle &obj) override;

		//! @brief Draw a sprite.
		//! @param obj The sprite to draw.
		//! @return True if the draw was successful. False otherwise.
		bool draw(Drawables::Sprite &obj) override;

		//! @brief Draw a text.
		//! @param obj The text to draw.
		//! @return True if the draw was successful. False otherwise.
		bool draw(Drawables::Text &obj) override;

		//! @brief Refresh the screen, clear left-overs and draw requested objects.
		bool refresh() override;

		//! @brief Gives the library type
		//! @return A value of the enum ModType representing the type of the library
		ModInfo::Modtype getType() const override;

		//! @brief Load a sprite
		//! @param path The path to the texture to load
		//! @return Return true if the texture was successfully loaded. False otherwise
		bool load(const std::string &type, const std::string &path) override;

		//! @brief Unload a sprite
		//! @param path The path to the texture to load
		void unload(const std::string &type, const std::string &path) override;

		//! @brief Unload all sprites loaded.
		void unloadAll() override;

		//! @brief Play a sound
		void playSound(Sound &sound) override;
	};
}