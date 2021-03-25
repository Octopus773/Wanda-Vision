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
		//! @brief The x position (in percentage)
		unsigned x;
		//! @brief The y position (in percentage)
		unsigned y;
		//! @brief The ID of this click.
		unsigned id;
	};
}