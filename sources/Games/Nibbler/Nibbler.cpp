//
// Created by Zoe Roux on 3/29/21.
//

#include "Common/Drawables/Rectangle.hpp"
#include "Common/Drawables/Sprite.hpp"
#include "Common/Drawables/Text.hpp"
#include "Common/Drawables/Line.hpp"
#include "Nibbler.hpp"
#include "Common/Events/KeyBoardEvent.hpp"
#include "Exceptions/WrongMapChar.hpp"
#include <iostream>
#include <Common/Drawables/Circle.hpp>
#include <algorithm>

namespace Arcade::Nibbler
{
	bool Nibbler::init()
	{
		srand(time(nullptr));
		this->_resources.emplace_back(std::make_pair("sprite", snakeCorpFilename));
		this->_resources.emplace_back(std::make_pair("sprite", snakeHeadFilename));
		this->_resources.emplace_back(std::make_pair("sprite", snakeTailFilename));
		this->_resources.emplace_back(std::make_pair("sprite", smallFoodFilename));
		this->_resources.emplace_back(std::make_pair("sprite", largeFoodFilename));
		this->_resources.emplace_back(std::make_pair("sprite", snakeTurn1Filename));
		this->_resources.emplace_back(std::make_pair("sprite", snakeTurn2Filename));
		this->_resources.emplace_back(std::make_pair("sprite", "assets/nibbler/nibbler_background.png"));
		this->_resources.emplace_back(std::make_pair("font", "assets/fonts/PressStart2P.ttf"));

		this->_playerDrawable = Drawables::Sprite();
		this->_playerDrawable.sizeY = mapTileLength;
		this->_playerDrawable.sizeX = mapTileLength;
		this->_playerDrawable.color = 0;
		this->_playerDrawable.rotation = 270;
		this->_playerPosition = {16 * mapTileLength, 15 * mapTileLength};
		this->_playerDrawable.x = this->_playerPosition.first;
		this->_playerDrawable.y = this->_playerPosition.second;
		this->_playerDrawable.path = snakeCorpFilename;

		Drawables::Rectangle fallbackRectangle;
		fallbackRectangle.x = this->_playerPosition.first;
		fallbackRectangle.y = this->_playerPosition.second;
		fallbackRectangle.endX = fallbackRectangle.x + mapTileLength;
		fallbackRectangle.endY = fallbackRectangle.y + mapTileLength;
		fallbackRectangle.color = 0xFFFB00FF;
		this->_playerDrawable.fallback = std::make_shared<Drawables::Rectangle>(fallbackRectangle);

		this->_scoreDrawable = Drawables::Text();
		this->_scoreDrawable.path = "assets/fonts/PressStart2P.ttf";
		this->_scoreDrawable.fontSize = 30;
		this->_scoreDrawable.color = 0xFFFFFFFF;
		this->_scoreDrawable.x = 5;
		this->_scoreDrawable.y = 5;
		this->_scoreDrawable.text = "Score: ";

		this->_background = Drawables::Sprite();
		this->_background.x = 50;
		this->_background.y = 50;
		this->_background.sizeX = 100;
		this->_background.sizeY = 100;
		this->_background.path = "assets/nibbler/nibbler_background.png";
		fallbackRectangle.x = 0;
		fallbackRectangle.y = 0;
		fallbackRectangle.endX = 100;
		fallbackRectangle.endY = 100;
		fallbackRectangle.color = 0xA2D049FF;
		this->_background.fallback = std::make_shared<Drawables::Rectangle>(fallbackRectangle);

		this->_map = this->_createMapFromVector({
			                                        "                         ",
			                                        "       b         b       ",
			                                        "       b         b       ",
			                                        "       b         b       ",
			                                        "                         ",
			                                        "                         ",
			                                        "  b                   b  ",
			                                        "   b                 b   ",
			                                        "   b       bbb       b   ",
			                                        "   b      bbbbb      b   ",
			                                        "  b       bbbbb       b  ",
			                                        "          bbbbb          ",
			                                        "           bbb           ",
			                                        "       b         b       ",
			                                        "      b           b      ",
			                                        "      b           b      ",
			                                        "       b         b       ",
			                                        "                         ",
			                                        "     b             b     ",
			                                        "     b             b     ",
			                                        "     b             b     ",
			                                        "           bbb           ",
			                                        "           bbb           ",
			                                        "                         ",},
		                                        mapOffsetTileY, mapOffsetTileX);

		this->_startGame();
		return true;
	}

	bool Nibbler::close()
	{
		return true;
	}

	void Nibbler::_startGame()
	{
		this->_internalClock = 0;
		this->_diffClock = 0;
		this->_drawables.clear();
		this->_food.clear();
		this->_shouldClose = false;

		this->_gameScore = 0;
		this->_playerPosition = {16 * mapTileLength, 15 * mapTileLength};
		this->_moves = {0};
		this->_playerMovement = {0, 0};
		this->_playerDrawable.rotation = 0;

		this->_moves.moveY = -1;
		this->_snake.clear();
		this->_playerDrawable.rotation = 270;
		this->_snake.emplace_back(this->_createSnakeCorpPart(this->_playerDrawable));
		this->_snake[0].path = snakeHeadFilename;
		this->_playerDrawable.y += mapTileLength;
		this->_snake.emplace_back(this->_createSnakeCorpPart(this->_playerDrawable));
		this->_playerDrawable.y += mapTileLength;
		this->_snake.emplace_back(this->_createSnakeCorpPart(this->_playerDrawable));
		this->_playerDrawable.y += mapTileLength;
		this->_snake.emplace_back(this->_createSnakeCorpPart(this->_playerDrawable));
		this->_snake.back().path = snakeTailFilename;
	}

	bool Nibbler::shouldClose()
	{
		return this->_shouldClose;
	}

	ModInfo::Modtype Nibbler::getType() const
	{
		return ModInfo::GAME;
	}

	const std::vector<std::pair<std::string, std::string>> &Nibbler::getResources() const
	{
		return this->_resources;
	}

	const std::vector<std::unique_ptr<Drawables::ADrawable>> &Nibbler::getDrawables()
	{
		this->_drawables.clear();
		this->_drawables.push_back(std::make_unique<Drawables::Sprite>(this->_background));
		for (auto i : this->_snake) {
			i.x += mapTileLength / 2;
			i.y += mapTileLength / 2;
			this->_drawables.emplace_back(std::make_unique<Drawables::Sprite>(i));
		}
		for (auto i : this->_food) {
			i.x += mapTileLength / 2;
			i.y += mapTileLength / 2;
			this->_drawables.emplace_back(std::make_unique<Drawables::Sprite>(i));
		}
		for (const auto &i : this->_map) {
			this->_drawables.emplace_back(std::make_unique<Drawables::Sprite>(i));
		}
		this->_drawables.push_back(std::make_unique<Drawables::Text>(this->_scoreDrawable));
		return this->_drawables;
	}

	const std::vector<Sound> &Nibbler::getSounds()
	{
		return this->_sounds;
	}

	void Nibbler::addTicks(unsigned int tick)
	{
		this->_internalClock += tick;

		if (this->_internalClock < this->_diffClock + this->_ticksPerFrame) {
			return;
		}
		this->_diffClock = this->_internalClock;
		for (int i = (tick > this->_ticksPerFrame) ? tick / this->_ticksPerFrame : 1; i; i--) {
			this->_processMovement();
			this->_processScore();
			this->_updateSnakePositions();
			this->_shouldClose = this->_isGameEnded();
		}
		this->_moves.moveX = 0;
		this->_moves.moveY = 0;
	}

	void Nibbler::restart()
	{
		this->_startGame();
	}

	void Nibbler::handleEvent(Event &event)
	{
		try {
			auto key = dynamic_cast<Events::KeyboardEvent &>(event);
			if (key.type == Event::KeyUp || key.type == Event::KeyDown)
				return;
			switch (key.key) {
			case Events::KeyboardEvent::UP_ARROW:
			case Events::KeyboardEvent::KEY_Z:
				this->_moves.moveY = std::min(-1, this->_moves.moveY + 1);
				break;
			case Events::KeyboardEvent::DOWN_ARROW:
			case Events::KeyboardEvent::KEY_S:
				this->_moves.moveY = std::max(1, this->_moves.moveY - 1);
				break;
			case Events::KeyboardEvent::RIGHT_ARROW:
			case Events::KeyboardEvent::KEY_D:
				this->_moves.moveX = std::min(1, this->_moves.moveX + 1);
				break;
			case Events::KeyboardEvent::LEFT_ARROW:
			case Events::KeyboardEvent::KEY_Q:
				this->_moves.moveX = std::max(-1, this->_moves.moveX - 1);
				break;
			default:
				return;
			}
		}
		catch (const std::bad_cast &) { }
	}

	unsigned long Nibbler::getScore()
	{
		return this->_gameScore;
	}

	std::vector<Drawables::Sprite> Nibbler::_createMapFromVector(const std::vector<std::string> &map, int hOffset, int vOffset)
	{
		std::vector<Drawables::Sprite> ret;
		int xIndex = -1;
		int yIndex = -1;

		for (const auto &i : map) {
			yIndex++;
			xIndex = -1;
			for (const auto &j : i) {
				xIndex++;
				if (j == MapChar::NOTHING) {
					continue;
				}
				ret.emplace_back(this->_getSpriteFromChar(j, xIndex + vOffset, yIndex + hOffset));
			}
		}
		return ret;
	}

	Drawables::Rectangle Nibbler::_getRectangleFromChar(char c, int xIndex, int yIndex)
	{
		Drawables::Rectangle rect;

		switch (c) {
		case MapChar::BUSH:
			rect.x = xIndex * mapTileLength;
			rect.y = yIndex * mapTileLength;
			rect.endX = rect.x + mapTileLength;
			rect.endY = rect.y + mapTileLength;
			rect.color = mapBushColor;
			return rect;
		case MapChar::BIG_FOOD:
			rect.x = (xIndex * mapTileLength) + 1;
			rect.y = (yIndex * mapTileLength) + 1;
			rect.endX = rect.x + mapTileLength - 2;
			rect.endY = rect.y + mapTileLength - 2;
			rect.color = 0xFCBA03FF;
			return rect;
		case MapChar::SMALL_FOOD:
			rect.x = (xIndex * mapTileLength) + 1;
			rect.y = (yIndex * mapTileLength) + 1;
			rect.endX = rect.x + mapTileLength - 2;
			rect.endY = rect.y + mapTileLength - 2;
			rect.color = 0xFF0000FF;
			return rect;
		default: throw WrongMapChar(c);
		}
	}

	bool Nibbler::_collideWithWallMap(int x, int y, int w, int h)
	{
		for (const auto &i : this->_map) {
			try {
				auto rect = dynamic_cast<Drawables::Rectangle &>(*i.fallback);
				if (rect.color != mapBushColor)
					continue;
				if (x + w <= rect.x
					|| y + h <= rect.y
					|| rect.endX <= x
					|| rect.endY <= y) {
					continue;
				}
				return true;
			} catch (const std::bad_cast &) { }
		}
		return false;
	}

	Drawables::Sprite Nibbler::_getSpriteFromChar(char c, int xIndex, int yIndex)
	{
		Drawables::Sprite ret;

		ret.x = xIndex * mapTileLength;
		ret.y = yIndex * mapTileLength;
		switch (c) {
		case MapChar::BUSH:
			ret.fallback = std::make_shared<Drawables::Rectangle>(this->_getRectangleFromChar(c, xIndex, yIndex));
			return ret;
		case MapChar::BIG_FOOD:
			ret.sizeY = mapTileLength;
			ret.sizeX = mapTileLength;
			ret.x = xIndex * mapTileLength;
			ret.y = yIndex * mapTileLength;
			ret.path = largeFoodFilename;
			ret.rotation = 0;
			ret.fallback = std::make_shared<Drawables::Circle>(this->_getCircleFromChar(c, xIndex, yIndex));
			ret.color = 0;
			return ret;
		case MapChar::SMALL_FOOD:
			ret.sizeY = mapTileLength;
			ret.sizeX = mapTileLength;
			ret.x = xIndex * mapTileLength;
			ret.y = yIndex * mapTileLength;
			ret.path = smallFoodFilename;
			ret.rotation = 0;
			ret.fallback = std::make_shared<Drawables::Circle>(this->_getCircleFromChar(c, xIndex, yIndex));
			ret.color = 0;
			return ret;
		default: throw WrongMapChar(c);
		}
	}

	std::vector<Drawables::Sprite>::iterator Nibbler::_collideWithPacgumFood(int x, int y, int w, int h)
	{
		int index = -1;

		for (const auto &sprite : this->_food) {
			index++;
			try {
				if (sprite.path != largeFoodFilename && sprite.path != smallFoodFilename)
					continue;
				if (x + w <= sprite.x
				    || y + h <= sprite.y
				    || sprite.x + sprite.sizeX <= x
				    || sprite.y + sprite.sizeY <= y) {
					continue;
				}
				return this->_food.begin() + index;
			} catch (const std::bad_cast &) { }
		}
		return this->_food.end();
	}

	void Nibbler::_processMovement()
	{
		double newX;
		double newY;
		int &moveX = this->_playerMovement.first;
		int &moveY = this->_playerMovement.second;

		if (this->_moves.moveX && !moveX) {
			moveX = this->_moves.moveX > 0 ? 1 : -1;
			moveY = 0;
		} else if (this->_moves.moveY && !moveY) {
			moveY = this->_moves.moveY > 0 ? 1 : -1;
			moveX = 0;
		}
		newX = this->snakeSpeed * moveX * mapTileLength;
		newY = this->snakeSpeed * moveY * mapTileLength;

		if (newX) {
			if (this->_collideWithWallMap(newX + this->_playerPosition.first,
			                              this->_playerPosition.second,
			                              this->_playerDrawable.sizeX,
			                              this->_playerDrawable.sizeY)) {
				moveX = 0;
				newX = 0;
			}
			this->_playerPosition.first += newX;
		}
		if (newY) {
			if (this->_collideWithWallMap(this->_playerPosition.first,
			                              newY + this->_playerPosition.second,
			                              this->_playerDrawable.sizeX,
			                              this->_playerDrawable.sizeY)) {
				moveY = 0;
				newY = 0;
			}
			this->_playerPosition.second += newY;
		}

		if (moveY) {
			this->_playerDrawable.rotation = (moveY > 0) ? 90 : 270;
		}
		if (moveX) {
			this->_playerDrawable.rotation = (moveX > 0) ? 0 : 180;
		}
	}

	void Nibbler::_processScore()
	{
		auto it = this->_collideWithPacgumFood(this->_playerPosition.first,
		                                       this->_playerPosition.second,
		                                       this->_playerDrawable.sizeX,
		                                       this->_playerDrawable.sizeY);
		if (it != this->_food.end()) {
			this->_gameScore += (*it).path == this->largeFoodFilename ? 50 : 10;
			this->_increaseSnakeLength((*it).path == this->largeFoodFilename ? 3 : 1);
			this->_food.erase(it);
		}
		if (this->_food.empty()) {
			this->_ticksPerFrame -= 1000;
			this->_addFood((rand() % 3) + 1);
		}
		this->_scoreDrawable.text = "Score: " + std::to_string(this->_gameScore);
	}

	Drawables::Circle Nibbler::_getCircleFromChar(char c, int xIndex, int yIndex)
	{
		Drawables::Circle ret;

		switch (c) {
		case MapChar::BIG_FOOD:
			ret.size = 1;
			ret.x = (xIndex * mapTileLength) + (mapTileLength / 2.);
			ret.y = (yIndex * mapTileLength) + (mapTileLength / 2.);
			ret.fallback = std::make_shared<Drawables::Rectangle>(this->_getRectangleFromChar(c, xIndex, yIndex));
			ret.color = 0xFCBA03FF;
			return ret;
		case MapChar::SMALL_FOOD:
			ret.size = 1;
			ret.x = (xIndex * mapTileLength) + (mapTileLength / 2.);
			ret.y = (yIndex * mapTileLength) + (mapTileLength / 2.);
			ret.fallback = std::make_shared<Drawables::Rectangle>(this->_getRectangleFromChar(c, xIndex, yIndex));
			ret.color = 0xFF0000FF;
			return ret;
		default: throw WrongMapChar(c);
		}
	}

	bool Nibbler::_isGameEnded()
	{
		auto snakeHead = this->_snake.begin();

		if (snakeHead->x < 0
		    || snakeHead->x >= 100
		    || snakeHead->y < 0
		    || snakeHead->y >= 100) {
			return true;
		}
		return std::ranges::any_of(this->_snake.begin() + 1, this->_snake.end(), [snakeHead](auto i) {
			return i.x == snakeHead->x && i.y == snakeHead->y;
		});
	}

	int Nibbler::_getDisplayCoord(int coord)
	{
		return (coord / mapTileLength) * mapTileLength;
	}

	void Nibbler::_increaseSnakeLength(unsigned int length)
	{
		for (unsigned int i = 0; i < length; i++) {
			this->_snake.push_back(this->_createSnakeCorpPart(this->_snake.back()));
		}
	}

	Drawables::Sprite Nibbler::_createSnakeCorpPart(const Drawables::Sprite &reference)
	{
		Drawables::Sprite sprite = reference;
		Drawables::Rectangle rect = *dynamic_cast<Drawables::Rectangle *>(sprite.fallback.get());

		sprite.fallback = std::make_shared<Drawables::Rectangle>(rect);
		return sprite;
	}

	void Nibbler::_updateSnakePositions()
	{
		int prevX;
		int prevY;
		int prevR;
		std::string prevP;
		int newX = this->_playerPosition.first;
		int newY = this->_playerPosition.second;
		int newR = this->_playerDrawable.rotation;
		std::string newP = this->_getCorrectTurnFilename(newR);
		int index = 0;

		for (auto &i : this->_snake) {
			prevX = i.x;
			prevY = i.y;
			prevR = i.rotation;
			if (index > 0) {
				prevP = i.path;
			}
			i.x = newX;
			i.y = newY;
			i.rotation = newR;
			if (index > 0) {
				i.path = newP;
			}
			auto rect = dynamic_cast<Drawables::Rectangle *>(i.fallback.get());
			rect->x = newX;
			rect->y = newY;
			rect->endX = rect->x + mapTileLength;
			rect->endY = rect->y + mapTileLength;
			newX = prevX;
			newY = prevY;
			newR = prevR;
			if (index > 0) {
				newP = prevP;
			}
			index++;
		}
		this->_snake.back().rotation = this->_snake[index - 2].rotation;
		this->_snake.back().path = snakeTailFilename;
	}

	void Nibbler::_addFood(int number)
	{
		int maxIterations = 100;
		int x;
		int y;

		for (int i = 0; i < number; i++) {
			x = rand() % 25;
			y = rand() % 25;
			for (int j = 0; this->_isObstacleAtCoords(x * mapTileLength, y * mapTileLength) && j < maxIterations; j++) {
				x = rand() % 25;
				y = rand() % 25;
			}
			this->_food.emplace_back(this->_getSpriteFromChar((rand() % 10 < 7) ? MapChar::SMALL_FOOD : MapChar::BIG_FOOD, x, y));
		}
	}

	bool Nibbler::_isObstacleAtCoords(int x, int y)
	{
		return this->_isSnakeAtCoords(x, y) || this->_isFoodAtCoords(x, y) || this->_isMapAtCoords(x, y);
	}

	bool Nibbler::_isSnakeAtCoords(int x, int y)
	{
		return std::ranges::any_of(this->_snake.begin(), this->_snake.end(), [x, y](auto i) {
			return i.x == x && i.y == y;
		});
	}

	bool Nibbler::_isFoodAtCoords(int x, int y)
	{
		return std::ranges::any_of(this->_food.begin(), this->_food.end(), [x, y](auto i) {
			return i.x == x && i.y == y;
		});
	}

	bool Nibbler::_isMapAtCoords(int x, int y)
	{
		return std::ranges::any_of(this->_map.begin(), this->_map.end(), [x, y](auto i) {
			return i.x == x && i.y == y;
		});
	}

	std::string Nibbler::_getCorrectTurnFilename(int index)
	{
		auto &snakeHead = this->_snake.front();
		auto &firstPart = this->_snake.front();

		if (index == firstPart.rotation) {
			return std::string(snakeCorpFilename);
		}
		switch (firstPart.rotation) {
		case 0: return std::string(index == 270 ? snakeTurn1Filename : snakeTurn2Filename);
		case 90: return std::string(index == 0 ? snakeTurn1Filename : snakeTurn2Filename);
		case 180: return std::string(index == 270 ? snakeTurn2Filename : snakeTurn1Filename);
		case 270:
		default: return std::string(index == 0 ? snakeTurn2Filename : snakeTurn1Filename);
		}
	}

}

extern "C" Arcade::ModInfo getHeader()
{
	Arcade::ModInfo info;
	info.name = "Nibbler";
	info.type = Arcade::ModInfo::GAME;
	info.magicNumber = Arcade::MagicNumber;
	return info;
}

extern "C" Arcade::IModule *getModule()
{
	return new Arcade::Nibbler::Nibbler;
}