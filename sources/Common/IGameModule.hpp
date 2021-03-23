/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** IGameLibrary
*/

#pragma once

#include "Common/ModInfo.hpp"
#include "Common/GameObject.hpp"
#include "Common/Module.hpp"
#include "Common/Event.hpp"
#include <vector>

namespace Arcade
{
	//! @brief The interface of all games.
	class IGameModule : public IModule
	{
	public:
		//! @brief Virtual destructor
		~IGameModule() override = default;

		//! @brief Return a list of game objects to display.
		//! @return The list of objects
		virtual const std::vector<GameObject> &getObjects() = 0;

		//! @brief Advance the game of x seconds
		//! @param tick The number of ticks that occured since the last call.
		virtual void addTicks(unsigned tick) = 0;

		//! @brief Restart the game.
		virtual void restart() = 0;

		//! @brief Handle one event (A key press, a click, a close event...)
		//! @param event The event to handle.
		virtual void handleEvent(Event event) = 0;

		//! @brief Get the score (used for saving/displaying)
		virtual unsigned long getScore() = 0;
	};
}
