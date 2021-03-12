/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** ClickEvent
*/

#pragma once

#include "Event.hpp"

namespace Arcade::Event
{
	struct ClickEvent : public Event
	{
		//! @brief The x position (in percentage)
		unsigned x;
		//! @brief The y position (in percentage)
		unsigned y;
		//! @brief The ID of this click.
		unsigned id;
	}
}