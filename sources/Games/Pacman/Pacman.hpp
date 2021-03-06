//
// Created by Zoe Roux on 3/29/21.
//

#pragma once

#include <map>
#include "Common/IGameModule.hpp"
#include "Common/Drawables/Line.hpp"
#include "Common/Drawables/Circle.hpp"
#include <array>

namespace Arcade::Pacman
{
	///! @brief The Pacman game's module.
	class Pacman : public IGameModule
	{
	private:
		//! @brief The ghost struct
		struct Ghost {
			int speed;
			Drawables::Sprite drawable;
		};

		//! @brief Struct used to keep pending moves.
		struct PendingMoves {
			//! @brief X direction of the player
			int moveX;
			//! @brief Y direction of the player
			int moveY;
		};

		enum MapChar {
			//! @brief Represents a space, nothing should be drawned with it
			//! @info It's used for padding
			NOTHING = ' ',
			//! @brief Representing a wall in the map
			WALL = 'w',
			//! @brief Representing a small pacgum in the map
			SMALL_PACGUM = '.',
			//! @brief Representing a big pacgum in the map
			BIG_PACGUM = 'P',
			//! @brief Ghost Blinky
			BLINKY = 'B',
			//! @brief Ghost Inky
			INKY = 'I',
			//! @brief Ghost Clyde
			CLYDE = 'C',
			//! @brief A black rectangle 1x4 (Used to hide some parts of the map)
			HIDE_RECTANGLE = '_'
		};

		//! @brief The position of the player.
		std::pair<double, double> _playerPosition;
		//! @brief The movement of the player.
		std::pair<int, int> _playerMovement;
		//! @brief The player's drawable
		Drawables::Sprite _playerDrawable;
		//! @brief Information of all the ghosts
		Ghost _ghosts;
		//! @brief If the game has ended
		bool _shouldClose;
		//! @brief Game Score
		long _gameScore = 0;
		//! @brief Text element to draw the score to the screen
		Drawables::Text _scoreDrawable;
		//! @brief Resources needed by this game.
		std::vector<std::pair<std::string, std::string>> _resources = {};
		//! @brief Drawables that will be displayed.
		std::vector<std::unique_ptr<Drawables::ADrawable>> _drawables = {};
		//! @brief Sounds that will be started in the next frame
		std::vector<Sound> _sounds = {};
		//! @brief Game map
		std::vector<Drawables::Sprite> _map = {};
		//! @brief Pending moves.
		PendingMoves _moves = {};
		//! @brief The length of a map tile
		static constexpr int mapTileLength = 4;
		//! @brief The offset of the map in number of mapTileLength for the X axis
		static constexpr int mapOffsetTileX = 1;
		//! @brief The offset of the map in number of mapTileLength for the Y axis
		static constexpr int mapOffsetTileY = 5;
		//! @brief The color of the walls
		//! @info This color is used to check if the block is collidable or not
		static constexpr int mapWallColor = 0x0000FFFF;
		//! @brief The speed of pacman (the player)
		static constexpr float pacmanSpeed = .000020;
		//! @brief Resource location for the large pacgum sprite
		static constexpr std::string_view largePacgumFilename = "assets/pacman/large_pacgum.png";
		//! @brief Resource location for the small pacgum sprite
		static constexpr std::string_view smallPacgumFilename = "assets/pacman/small_pacgum.png";

		//! @brief Gives the correct Drawables to be able to draw the map on the screen
		//! @param map The vector of string to represent the actual map (one type of char represent a type/config of drawable)
		//! @param vOffset The vertical offset in percentage
		//! @param hOffset The horizontal offset in percentage
		//! @info Offset can be set to a negative value the function will simply add the offset given to the offset calculated
		//! @warning Sprites are only used for a "base drawable" some sprites will be purposely ill formed, in order to call the fallback
		std::vector<Drawables::Sprite> _createMapFromVector(const std::vector<std::string> &map, int hOffset, int vOffset);
		//! @brief Get the correct Rectangle and correctly filled from a char
		//! @param c The template type
		//! @param xIndex The x position of the char in the map
		//! @param yIndex The y position of the char in the map
		//! @warning This function uses hard coded templates for each char. This function should only be used with the map context in mind
		//! @return A instance of a Rectangle
		//! @throw WrongMapChar when no matching char is found
		Drawables::Rectangle _getRectangleFromChar(char c, int xIndex, int yIndex);
		//! @brief Tells if you colliding with one of the rectangle of the _map member
		//! @param x The x percentage
		//! @param y The y percentage
		//! @param w The width in percentage
		//! @param h The the height in percentage
		//! @return True if the coords are colliding, otherwise false
		bool _collideWithWallMap(int x, int y, int w, int h);
		//! @brief Get the correct Sprite and correctly filled from a char
		//! @param c The template type
		//! @param xIndex The x position of the char in the map
		//! @param yIndex The y position of the char in the map
		//! @warning This function uses hard coded templates for each char. This function should only be used with the map context in mind
		//! @return A instance of a Sprite
		//! @throw WrongMapChar when no matching char is found
		Drawables::Sprite _getSpriteFromChar(char c, int xIndex, int yIndex);
		//! @brief Get the correct Circle and correctly filled from a char
		//! @param c The template type
		//! @param xIndex The x position of the char in the map
		//! @param yIndex The y position of the char in the map
		//! @warning This function uses hard coded templates for each char. This function should only be used with the map context in mind
		//! @return A instance of a Circle
		//! @throw WrongMapChar when no matching char is found
		Drawables::Circle _getCircleFromChar(char c, int xIndex, int yIndex);
		//! @brief Tells if you colliding with one of the pacgums of the _map member
		//! @param x The x percentage
		//! @param y The y percentage
		//! @param w The width in percentage
		//! @param h The the height in percentage
		//! @return The pacgum you collided, otherwise
		std::vector<Drawables::Sprite>::iterator _collideWithPacgumMap(int x, int y, int w, int h);
		//! @brief Checks collisions and moves the player, rotate texture, etc...
		//! @param ticks Delta time (number of ticks between two functions calls)
		//! @info The movement will be kept until hitting an obstacle or a new input is detected
		void _processPlayerMovement(unsigned int ticks);
		//! @brief Checks the collision with Pacgums and ghosts and update the score
		void _processScore();
		//! @brief Start the game and initialise variables to their start values
		void  _startGame();
		//! @brief Tells if the game has ended
		bool _isGameEnded();
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