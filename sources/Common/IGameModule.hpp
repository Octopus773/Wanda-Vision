/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** IGameLibrary
*/

#pragma once

#include "Common/ModInfo.hpp"
#include "Common/Drawables/ADrawable.hpp"
#include "Common/Module.hpp"
#include "Common/Events/Event.hpp"
#include "Common/Sound.hpp"
#include <vector>
#include <memory>
#include <string>

namespace Arcade
{
	//! @brief The interface of all games.
	class IGameModule : public IModule
	{
	public:
		//! @brief Virtual destructor
		~IGameModule() override = default;

		//! @brief Get resources to preload.
		//! @info Only called once.
		//! @return A vector of tupple of (type of resource, path of the resource).
		virtual const std::vector<std::pair<std::string, std::string>> &getResources() const = 0;

		//! @brief Return a list of drawables to display.
		//! @return The list of objects
		virtual const std::vector<std::unique_ptr<Drawables::ADrawable>> &getDrawables() = 0;

		//! @brief Return a list of sounds to make.
		//! @return The list of sounds
		virtual const std::vector<Sound> &getSounds() = 0;

		//! @brief Advance the game of x seconds
		//! @param tick The number of ticks that occured since the last call.
		virtual void addTicks(unsigned tick) = 0;

		//! @brief Restart the game.
		virtual void restart() = 0;

		//! @brief Handle one event (A key press, a click, a close event...)
		//! @param event The event to handle.
		virtual void handleEvent(Event &event) = 0;

		//! @brief Get the score (used for saving/displaying)
		virtual unsigned long getScore() = 0;
	};
}
