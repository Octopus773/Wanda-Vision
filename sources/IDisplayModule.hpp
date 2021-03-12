/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** IDisplayLibrary
*/

#pragma once

namespace Arcade
{
	//! @brief The interface of every display modules
	class IDisplayModule
	{
	public:
		//! @brief Virtual destructror
		virtual ~IDisplayModule() = default;

		//! @brief Draw a line.
		//! @param obj The line to draw.
		virtual void drawLine(LineObject obj);

		//! @brief Draw a rectangle.
		//! @param obj The rectangle to draw.
		virtual void drawRectangle(RectangleObject obj);

		//! @brief Draw a circle.
		//! @param obj The circle to draw.
		virtual void drawCircle(CircleObject obj);
		
		//! @brief Draw a sprite.
		//! @param obj The sprite to draw.
		virtual void drawSprite(SpriteObject obj);
	};
}