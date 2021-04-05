//
// Created by Zoe Roux on 3/29/21.
//

#pragma once

#include <map>
#include "Common/IGameModule.hpp"
#include "Common/Drawables/Line.hpp"
#include <array>

namespace Arcade::Pacman
{
	///! @brief The Pacman game's module.
	class Pacman : public IGameModule
	{
	private:
		//! @brief Struct used to keep pending moves.
		struct PendingMoves {
			//! @brief X direction of the player
			int moveX;
			//! @brief Y direction of the player
			int moveY;
		};

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
		//! @brief Game map
		std::vector<Drawables::Rectangle> _map = {};
		//! @brief Pending moves.
		PendingMoves _moves = {};
		//! @brief The length of a map tile
		static constexpr int mapTileLength = 5;

		//! @brief Gives the correct Rectangles to be able to draw the map on the screen
		//! @param map The vector of string to represent the actual map (one type of char represent a type/config of drawable)
		//! @param vOffset The vertical offset in percentage
		//! @param hOffset The horizontal offset in percentage
		//! @info Offset can be set to a negative value the function will simply add the offset given to the offset calculated
		std::vector<Drawables::Rectangle> createMapFromVector(const std::vector<std::string> &map, int hOffset, int vOffset);
		//! @brief Get the correct Rectangle and correctly filled from a char
		//! @param c The template type
		//! @param xIndex The x position of the char in the map
		//! @param yIndex The y position of the char in the map
		//! @warning This function uses hard coded templates for each char. This function should only be used with the map context in mind
		//! @return A instance of a Rectangle
		//! @throw WrongMapChar when no matching char is found
		Drawables::Rectangle getRectangleFromChar(char c, int xIndex, int yIndex);
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