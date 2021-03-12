/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** IDisplayLibrary
*/

#pragma once

#include "Module.hpp"
#include "GameObjects/LineObject.hpp"
#include "GameObjects/RectangleObject.hpp"
#include "GameObjects/CircleObject.hpp"
#include "GameObjects/SpriteObject.hpp"
#include "Event.hpp"
#include <list>

namespace Arcade
{
	//! @brief The interface of every display modules
	class IDisplayModule : public IModule
	{
	public:
		//! @brief Virtual destructror
		virtual ~IDisplayModule() = default;

		//! @brief Pull events (Keys, Clicks, Closes...)
		//! @return The list of events that occured.
		virtual std::list<Event> pullEvents() = 0;

		//! @brief Draw a line.
		//! @param obj The line to draw.
		virtual void drawLine(GameObject::LineObject obj) = 0;

		//! @brief Draw a rectangle.
		//! @param obj The rectangle to draw.
		virtual void drawRectangle(GameObject::RectangleObject obj) = 0;

		//! @brief Draw a circle.
		//! @param obj The circle to draw.
		virtual void drawCircle(GameObject::CircleObject obj) = 0;
		
		//! @brief Draw a sprite.
		//! @param obj The sprite to draw.
		virtual void drawSprite(GameObject::SpriteObject obj) = 0;
	};
}