//
// Created by Zoe Roux on 3/29/21.
//

#pragma once

#include <map>
#include "Common/IGameModule.hpp"

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
		std::pair<double, double> _playerPosition;
		//! @brief Current draw type of the player.
		DrawType _drawType;

		//! @brief Pending moves.
		PendingMoves _moves;
		//! @brief Move speed of the player
		std::map<DrawType, double> _moveSpeeds = {
			{None, 1000},
			{Fast, 1000},
			{Slow, 500}
		};

		//! @brief Resources needed by this game.
		std::vector<std::string> _resources = {};
		//! @brief Drawables that will be displayed.
		std::vector<std::unique_ptr<ADrawable>> _drawables = {};
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

		//! @brief Get sprites to preload.
		//! @info Only called once.
		const std::vector<std::string> &getSprites() const override;

		//! @brief Return a list of drawables to display.
		//! @return The list of objects
		const std::vector<std::unique_ptr<ADrawable>> &getDrawables() override;

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