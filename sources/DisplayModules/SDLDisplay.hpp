//
// Created by cbihan on 3/22/21.
//

#pragma once

#include "IDisplayModule.hpp"
namespace Arcade
{
	//! @brief Implementation of the SDL Graphic Library
	class SDLDisplay : public IDisplayModule {
	public:
		SDLDisplay() = default;
		~SDLDisplay() override =  default;
		SDLDisplay(const SDLDisplay &) = default;
		SDLDisplay &operator=(const SDLDisplay &) = default;

		//! @brief Pull events (Keys, Clicks, Closes...)
		//! @return The list of events that occured.
		std::list<Event> pullEvents() override;

		//! @brief Draw a line.
		//! @param obj The line to draw.
		void drawLine(GameObjects::LineObject obj) override;

		//! @brief Draw a rectangle.
		//! @param obj The rectangle to draw.
		void drawRectangle(GameObjects::RectangleObject obj) override;

		//! @brief Draw a circle.
		//! @param obj The circle to draw.
		void drawCircle(GameObjects::CircleObject obj) override;

		//! @brief Draw a sprite.
		//! @param obj The sprite to draw.
		void drawSprite(GameObjects::SpriteObject obj) override;

		//! @brief Refresh the screen, clear left-overs and draw requested objects.
		void refresh() const override;
	};

}