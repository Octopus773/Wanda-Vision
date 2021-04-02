//
// Created by Zoe Roux on 3/29/21.
//

#pragma once

#include <map>
#include "Common/IGameModule.hpp"
#include "Common/Drawables/Line.hpp"

namespace Arcade::Pacman
{
	///! @brief The Pacman game's module.
	class Pacman : public IGameModule
	{
	private:

		//! @brief The position of the player.
		std::pair<double, double> _playerPosition = {50, 50};

		//! @brief The player's drawable
		Drawables::Sprite _playerDrawable;

		//! @brief Resources needed by this game.
		std::vector<std::pair<std::string, std::string>> _resources = {};
		//! @brief Drawables that will be displayed.
		std::vector<std::unique_ptr<Drawables::ADrawable>> _drawables = {};
		//! @brief Sounds that will be started in the next frame
		std::vector<Sound> _sounds = {};

		std::vector<Drawables::Rectangle> map;
	public:
		//! @brief Initialize this library. (Create windows & so on)
		//! @return True if the initialization was successful. False otherwise.
		bool init() override;

		//! @brief Allow to say to the library to shutdown and free it's content
		//! @return True if the shutdown was successful. False otherwise.
		bool close() override;

		//! @brief Should this module be closed?
		//! @return True if this module should be closed. False otherwise.
		bool shouldClose() override;

		//! @brief Get the type of this module
		ModInfo::Modtype getType() const override;

		//! @brief Get resources to preload.
		//! @info Only called once.
		//! @return A vector of tuple of (type of resource, path of the resource).
		const std::vector<std::pair<std::string, std::string>> &getResources() const override;

		//! @brief Return a list of drawables to display.
		//! @return The list of objects
		const std::vector<std::unique_ptr<Drawables::ADrawable>> &getDrawables() override;

		//! @brief Return a list of sounds to make.
		//! @return The list of sounds
		const std::vector<Sound> &getSounds() override;

		//! @brief Advance the game of x seconds
		//! @param tick The number of ticks that occurred since the last call.
		void addTicks(unsigned tick) override;

		//! @brief Restart the game.
		void restart() override;

		//! @brief Handle one event (A key press, a click, a close event...)
		//! @param event The event to handle.
		void handleEvent(Event &event) override;

		//! @brief Get the score (used for saving/displaying)
		unsigned long getScore() override;


		//! @brief Default constructor
		Pacman() = default;
		//! @brief Default copy constructor
		Pacman(const Pacman &) = default;
		//! @brief Default destructor
		~Pacman() override = default;
		//! @brief Default assignment operator
		Pacman &operator=(const Pacman &) = default;
	};
}