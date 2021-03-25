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
	//! @brief Event called when the mouse moved.
	struct MouseMoveEvent : public Event
	{
		//! @brief The x position (in percentage)
		unsigned x;
		//! @brief The y position (in percentage)
		unsigned y;
	};
}