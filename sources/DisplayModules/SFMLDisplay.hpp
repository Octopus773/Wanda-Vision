//
// Created by cbihan on 4/6/21.
//

#pragma once

#include "Common/IDisplayModule.hpp"


namespace Arcade
{
	//! @brief Implementation of the SDL Graphic Library
	class SFMLDisplay : public IDisplayModule
	{
	private:

	public:
		//! @brief Default constructor
		//! @warning In order to properly use this class you must call the init member function
		SFMLDisplay() = default;
		//! @brief Default copy constructor.
		//! @warning You must call the close member function before the destructor if you called the init member function
		~SFMLDisplay() override =  default;
		//! @brief Default copy constructor.
		SFMLDisplay(const SFMLDisplay &) = default;
		//! @brief Default  assignment operator
		SFMLDisplay &operator=(const SFMLDisplay &) = default;

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


