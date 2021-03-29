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
			UNDEFINED = 0,
			LEFT = 1,
			MIDDLE = 2,
			RIGHT = 3,
			XBUTTON1 = 4,
			XBUTTON2 = 5
		};

		//! @brief The x position (in percentage)
		unsigned x;
		//! @brief The y position (in percentage)
		unsigned y;
		//! @brief The button of this click.
		MouseButton button;
	};
}