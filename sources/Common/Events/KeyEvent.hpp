/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** KeyEvent
*/

#pragma once

#include "Event.hpp"

namespace Arcade::Event
{
	struct KeyEvent : Event
	{
		//! @brief The key clicked
		unsigned key;
	};
}