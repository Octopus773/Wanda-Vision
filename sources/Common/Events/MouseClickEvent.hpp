/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** ClickEvent
*/

#pragma once

#include "Common/Events/Event.hpp"

namespace Arcade::Events
{
	//! @brief Event called after the mouse clicked (KeyDown, Hold or KeyUp)
	struct MouseClickEvent : public Event
	{
		//! @brief The enum for mouse buttons to allow standardized values between graphical libs
		enum MouseButton {
			LEFT = 0,
			MIDDLE = 1,
			RIGHT = 2,
			XBUTTON1 = 3,
			XBUTTON2 = 4
		};

		//! @brief The x position (in percentage)
		unsigned x;
		//! @brief The y position (in percentage)
		unsigned y;
		//! @brief The button of this click.
		MouseButton button;
	};
}