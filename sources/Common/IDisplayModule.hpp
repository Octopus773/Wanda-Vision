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
	};
}
