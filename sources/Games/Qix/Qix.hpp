//
// Created by Zoe Roux on 3/29/21.
//

#pragma once

#include <map>
#include "Common/IGameModule.hpp"
#include "Common/Drawables/Line.hpp"

namespace Arcade::Qix
{
	///! @brief The qix game's module.
	class Qix : public IGameModule
	{
	private:
		//! @brief Enum of draw types.
		enum DrawType {
			None,
			Slow,
			Fast
		};
		//! @brief Struct used to keep pending moves.
		struct PendingMoves {
			//! @brief X direction of the player
			int moveX;
			//! @brief Y direction of the player
			int moveY;
			//! @brief Draw type (fast, slow or none)
			DrawType draw;
		};

		//! @brief The position of the player.
		std::pair<double, double> _playerPosition = {50, 90};
		//! @brief Current draw type of the player.
		DrawType _drawType = None;

		//! @brief Pending moves.
		PendingMoves _moves = {};
		//! @brief Move speed of the player
		std::map<DrawType, double> _moveSpeeds = {
			{None, .0001},
			{Fast, .0001},
			{Slow, .00005}
		};

		//! @brief Start a new line at the current player's position.
		void _startLine();

		//! @brief The player's drawable
		Drawables::Circle _playerDrawable;
		//! @brief The list of lines of the current shape
		std::vector<Drawables::Line> _lines = {};

		//! @brief Resources needed by this game.
		std::vector<std::pair<std::string, std::string>> _resources = {};
		//! @brief Drawables that will be displayed.
		std::vector<std::unique_ptr<Drawables::ADrawable>> _drawables = {};
		//! @brief Sounds that will be started in the next frame
		std::vector<Sound> _sounds = {};
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
		Qix() = default;
		//! @brief Default copy constructor
		Qix(const Qix &) = default;
		//! @brief Default destructor
		~Qix() override = default;
		//! @brief Default assignment operator
		Qix &operator=(const Qix &) = default;
	};
}