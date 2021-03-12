/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** IGameLibrary
*/

#pragma once

#include "ModInfo.hpp"
#include "GameObject.hpp"
#include "Module.hpp"
#include "Event.hpp"
#include <vector>

namespace Arcade
{
	//! @brief The interface of all games.
	class IGameModule : public IModule
	{
	public:
		//! @brief Virtual destructor
		virtual ~IGameModule() = default;

		//! @brief Get the library's header.
		//! @info Used to verify the integrity of the lib.
		virtual ModInfo getHeader() const = 0;

		//! @brief Return a list of game objects to display.
		//! @return The list of objects
		virtual std::vector<GameObject> getObjects() = 0;

		//! @brief Advance the game of x seconds
		//! @param tick The number of ticks that occured since the last call.
		virtual void addTicks(unsigned tick) = 0;

		//! @brief Restart the game.
		virtual void restart() = 0;

		//! @brief Handle one event (A key press, a click, a close event...)
		//! @param event The event to handle.
		virtual void handleEvent(Event event) = 0;
	};
}