//
// Created by Zoe Roux on 3/29/21.
//

#pragma once

#include <map>
#include "Common/IGameModule.hpp"
#include "Common/Drawables/Line.hpp"
#include "Common/Drawables/Circle.hpp"
#include <array>

namespace Arcade::Nibbler
{
	///! @brief The Nibbler game's module.
	class Nibbler : public IGameModule
	{
	private:

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
			BUSH = 'b',
			//! @brief Representing a small food in the map
			SMALL_FOOD = '.',
			//! @brief Representing a big food in the map
			BIG_FOOD = 'P'
		};

		//! @brief The position of the player.
		std::pair<double, double> _playerPosition;
		//! @brief The movement of the player.
		std::pair<int, int> _playerMovement;
		//! @brief The player's drawable
		Drawables::Sprite _playerDrawable;
		//! THE snake
		std::vector<Drawables::Sprite> _snake;
		//! Food of the snake
		std::vector<Drawables::Sprite> _food;
		//! @brief background (or big green rectangle)
		Drawables::Sprite _background;
		//! @brief Internal clock
		unsigned long _internalClock = 0;
		//! @brief The number of ticks required per frame (ticks are in microseconds)
		unsigned long _ticksPerFrame = 190000;
		//! @brief A differential clock
		//! @info Used to update every
		long _diffClock = 0;
		//! @brief If the game has ended
		bool _shouldClose = false;
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
		static constexpr int mapOffsetTileX = 0;
		//! @brief The offset of the map in number of mapTileLength for the Y axis
		static constexpr int mapOffsetTileY = 0;
		//! @brief The color of the walls
		//! @info This color is used to check if the block is collidable or not
		static constexpr int mapBushColor = 0x0A8C06FF;
		//! @brief The speed the snake (the player) in cases per frame
		static constexpr float snakeSpeed = 1;
		//! @brief Resource location for the large food sprite
		static constexpr std::string_view largeFoodFilename = "assets/nibbler/big_food.png";
		//! @brief Resource location for the small food sprite
		static constexpr std::string_view smallFoodFilename = "assets/nibbler/small_food.png";
		//! @brief Resource location for the snake corp sprite
		static constexpr std::string_view snakeCorpFilename = "assets/nibbler/snake_corp.png";
		//! @brief Resource location for the snake head sprite
		static constexpr std::string_view snakeHeadFilename = "assets/nibbler/snake_head.png";
		//! @brief Resource location for the snake tail sprite
		static constexpr std::string_view snakeTailFilename = "assets/nibbler/snake_tail.png";
		//! @brief Resource location for the snake turn sprite
		static constexpr std::string_view snakeTurn1Filename = "assets/nibbler/snake_turn_0_270.png";
		//! @brief Resource location for the snake turn sprite
		static constexpr std::string_view snakeTurn2Filename = "assets/nibbler/snake_turn_270_90.png";

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
		std::vector<Drawables::Sprite>::iterator _collideWithPacgumFood(int x, int y, int w, int h);
		//! @brief Checks collisions and moves the player, rotate texture, etc...
		//! @info The movement will be kept until hitting an obstacle or a new input is detected
		void _processMovement();
		//! @brief Checks the collision with Food and update the score
		void _processScore();
		//! @brief Start the game and initialise variables to their start values
		void  _startGame();
		//! @brief Tells if the game has ended
		bool _isGameEnded();
		//! @brief Gte the display coords (to create a case effect movement)
		//! @param coord The real coordinates
		//! @return the coordinate to render on screen
		int _getDisplayCoord(int coord);
		//! @brief Add elements to the end of snake corp
		//! @param length The number of elements to add
		void _increaseSnakeLength(unsigned int length);
		//! @brief Create a corp part of the snake
		//! @param reference The element to create a deep copy on
		//! @return The drawable
		Drawables::Sprite _createSnakeCorpPart(const Drawables::Sprite &reference);
		//! @brief Update snake to the position of the next frame
		void _updateSnakePositions();
		//! @brief Add at random positions a piece of food
		//! @param number The number of food to add
		void _addFood(int number);
		//! @brief Tells if an obstacle is at these coords
		//! @param x The x coord
		//! @param y The y coord
		//! @return A bool if an obstacle is at those coords
		bool _isObstacleAtCoords(int x, int y);
		//! @brief Tells if the snake is at these coords
		//! @param x The x coord
		//! @param y The y coord
		//! @return A bool if the snake is at those coords
		bool _isSnakeAtCoords(int x, int y);
		//! @brief Tells if a food is at these coords
		//! @param x The x coord
		//! @param y The y coord
		//! @return A bool if a food is at those coords
		bool _isFoodAtCoords(int x, int y);
		//! @brief Tells if a map element is at these coords
		//! @param x The x coord
		//! @param y The y coord
		//! @return A bool if a map element is at those coords
		bool _isMapAtCoords(int x, int y);
		//! @brief Gives the correct turn filename for snake sprites
		//! @return The correct turn filename for sprite path
		std::string _getCorrectTurnFilename(int index);

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
		Nibbler() = default;
		//! @brief Default copy constructor
		Nibbler(const Nibbler &) = default;
		//! @brief Default destructor
		~Nibbler() override = default;
		//! @brief Default assignment operator
		Nibbler &operator=(const Nibbler &) = default;
	};
}