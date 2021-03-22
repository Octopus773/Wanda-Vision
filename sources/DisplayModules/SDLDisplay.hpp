//
// Created by cbihan on 3/22/21.
//

#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "IDisplayModule.hpp"
#include "Events/ClickEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/CloseEvent.hpp"

namespace Arcade
{
	//! @brief Implementation of the SDL Graphic Library
	class SDLDisplay : public IDisplayModule
	{
	private:
		//! @brief The window we're rendering on
		SDL_Window* _window = nullptr;
		//! @brief The surface of the window (renderer)
		SDL_Renderer *_windowRenderer = nullptr;
		//! @brief window height when init
		int _windowHeight = 480;
		//! @brief window width when init
		int _windowWidth = 640;
		//! @brief window title when init
		std::string _windowTitle = "SDL2 Display Module";
		//! @brief When true the caller should close this instance
		bool _shouldClose = false;

		//! @brief Binding of a constructor for KeyEvent struct
		//! @param key Value of key attribute of struct Events::KeyEvent
		//! @return A KeyEvent struct with it's values correctly filled
		static Events::KeyEvent createKeyEvent(unsigned key);
		//! @brief Binding of a constructor for ClickEvent struct
		//! @param x The x position (in percentage)
		//! @param y The y position (in percentage)
		//! @param id The ID of this click.
		//! @return A ClickEvent struct with it's values correctly filled
		static Events::ClickEvent createClickEvent(unsigned x, unsigned y, unsigned id);
		//! @brief Used to set the color of the SDL2 renderer
		//! @param color The color format: RRGGBBAA (1 byte each)
		void setRendererColor(unsigned color);
	public:
		SDLDisplay() = default;
		~SDLDisplay() override =  default;
		SDLDisplay(const SDLDisplay &) = default;
		SDLDisplay &operator=(const SDLDisplay &) = default;

		//! @brief Initialize this library. (Create windows & so on)
		//! @return True if the initialization was successful. False otherwise.
		bool init() override;

		//! @brief Allow to say to the library  t shutdown and free it's content
		//! @return True if the shutdown was successful. False otherwise.
		bool close() override;

		//! @brief Should this module be closed?
		//! @return True if this module should be closed. False otherwise.
		bool shouldClose() override;

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