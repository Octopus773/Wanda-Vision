/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Event
*/

#pragma once

namespace Arcade
{
	//! @brief An empty event used as a base class.
	struct Event
	{
		//! @brief List of events types
		enum Type {
			Unknown,
			Close,
			KeyDown,
			KeyUp,
			KeyHold,
			MouseMove,
		};

		//! @brief The type of this event.
		Type type;
		
		//! @brief Virtual destructor
		virtual ~Event() = default;
	};
}