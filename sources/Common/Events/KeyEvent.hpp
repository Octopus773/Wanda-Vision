/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** KeyEvent
*/

#pragma once

#include "Common/Event.hpp"

namespace Arcade::Events
{
	struct KeyEvent : public Event
	{
		//! @brief The key clicked
		unsigned key;
	};
}