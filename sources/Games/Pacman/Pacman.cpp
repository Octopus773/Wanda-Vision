//
// Created by Zoe Roux on 3/29/21.
//

#include "Common/Drawables/Rectangle.hpp"
#include "Common/Drawables/Sprite.hpp"
#include "Common/Drawables/Text.hpp"
#include "Common/Drawables/Line.hpp"
#include "Pacman.hpp"
#include "Common/Events/KeyBoardEvent.hpp"
#include "Exceptions/WrongMapChar.hpp"
#include <iostream>
#include <Common/Drawables/Circle.hpp>

namespace Arcade::Pacman
{
	bool Pacman::init()
	{
		this->_resources.emplace_back(std::make_pair("sprite", "assets/pacman/pacman.png"));
		this->_resources.emplace_back(std::make_pair("sprite", "assets/pacman/blinky.png"));
		this->_resources.emplace_back(std::make_pair("sprite", "assets/pacman/inky.png"));
		this->_resources.emplace_back(std::make_pair("sprite", "assets/pacman/clyde.png"));
		this->_resources.emplace_back(std::make_pair("font", "assets/fonts/angelina.ttf"));

		this->_playerDrawable = Drawables::Sprite();
		this->_playerDrawable.sizeY = mapTileLength;
		this->_playerDrawable.sizeX = mapTileLength;
		this->_playerDrawable.color = 0;
		this->_playerDrawable.rotation = 0;
		this->_playerDrawable.x = this->_playerPosition.first;
		this->_playerDrawable.y = this->_playerPosition.second;
		this->_playerDrawable.path = "assets/pacman/pacman.png";
		Drawables::Circle fallbackCircle;
		fallbackCircle.x = this->_playerPosition.first;
		fallbackCircle.y = this->_playerPosition.second;
		fallbackCircle.size = 2;
		fallbackCircle.color = 0xFFFB00FF;

		Drawables::Rectangle fallbackRectangle;
		fallbackRectangle.x = this->_playerPosition.first - (mapTileLength / 2);
		fallbackRectangle.y = this->_playerPosition.second - (mapTileLength / 2);
		fallbackRectangle.endX = fallbackRectangle.x + mapTileLength;
		fallbackRectangle.endY = fallbackRectangle.y + mapTileLength;
		fallbackRectangle.color = 0xFFFB00FF;
		fallbackCircle.fallback = std::make_shared<Drawables::Rectangle>(fallbackRectangle);
		this->_playerDrawable.fallback = std::make_shared<Drawables::Circle>(fallbackCircle);

		this->_scoreDrawable = Drawables::Text();
		this->_scoreDrawable.path = "assets/fonts/angelina.ttf";
		this->_scoreDrawable.fontSize = 30;
		this->_scoreDrawable.color = 0xFFFFFFFF;
		this->_scoreDrawable.x = 5;
		this->_scoreDrawable.y = 5;
		this->_scoreDrawable.text = "Score: ";
		this->_startGame();
		return true;
	}

	bool Pacman::close()
	{
		return true;
	}

	void Pacman::_startGame()
	{
		this->_drawables.clear();
		this->_map.clear();
		this->_map = this->_createMapFromVector({
			                                        "  wwwwwwwwwwwwwwwwwww  ",
			                                        "  wP.......w.......Pw  ",
			                                        "  w.ww.www.w.www.ww.w  ",
			                                        "  w.................w  ",
			                                        "  w.ww.w.wwwww.w.ww.w  ",
			                                        "  w....w...w...w....w  ",
			                                        "  wwww.www.w.www.wwww  ",
			                                        "     w.w.......w.w     ",
			                                        "wwwwww.w.wwwww.w.wwwwww",
			                                        "w .......wIBCw....... w",
			                                        "wwwwww.w.wwwww.w.wwwwww",
			                                        "__   w.w.......w.w   __",
			                                        "  wwww.www.w.www.wwww  ",
			                                        "  w....w...w...w....w  ",
			                                        "  w.ww.w.wwwww.w.ww.w  ",
			                                        "  w........ ........w  ",
			                                        "  w.ww.www.w.www.ww.w  ",
			                                        "  wP.......w.......Pw  ",
			                                        "  wwwwwwwwwwwwwwwwwww  "
		                                        }, mapOffsetTileY, mapOffsetTileX);

		this->_gameScore = 0;
		this->_playerPosition = {50, 20 * mapTileLength + (mapTileLength / 2)};
		this->_moves = {0};
		this->_playerMovement = {0, 0};
		this->_playerDrawable.rotation = 0;
	}

	bool Pacman::shouldClose()
	{
		return false;
	}

	ModInfo::Modtype Pacman::getType() const
	{
		return ModInfo::GAME;
	}

	const std::vector<std::pair<std::string, std::string>> &Pacman::getResources() const
	{
		return this->_resources;
	}

	const std::vector<std::unique_ptr<Drawables::ADrawable>> &Pacman::getDrawables()
	{
		this->_drawables.clear();
		this->_playerDrawable.x = this->_playerPosition.first;
		this->_playerDrawable.y = this->_playerPosition.second;
		this->_playerDrawable.fallback->x = this->_playerPosition.first;
		this->_playerDrawable.fallback->y = this->_playerPosition.second;
		if (auto fallback = dynamic_cast<Drawables::Rectangle *>(this->_playerDrawable.fallback->fallback.get())) {
			fallback->x = this->_playerPosition.first - (mapTileLength / 2);
			fallback->y = this->_playerPosition.second - (mapTileLength / 2);
			fallback->endX = fallback->x + mapTileLength;
			fallback->endY = fallback->y + mapTileLength;
		}

		this->_drawables.push_back(std::make_unique<Drawables::Sprite>(this->_playerDrawable));
		for (const auto &i : this->_map) {
			this->_drawables.emplace_back(std::make_unique<Drawables::Sprite>(i));
		}
		this->_drawables.push_back(std::make_unique<Drawables::Text>(this->_scoreDrawable));
		return this->_drawables;
	}

	const std::vector<Sound> &Pacman::getSounds()
	{
		return this->_sounds;
	}

	void Pacman::addTicks(unsigned int tick)
	{
		this->_processPlayerMovement(tick);
		this->_processScore();
		this->_moves.moveX = 0;
		this->_moves.moveY = 0;
	}

	void Pacman::restart()
	{
		this->_startGame();
	}

	void Pacman::handleEvent(Event &event)
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

	unsigned long Pacman::getScore()
	{
		return this->_gameScore;
	}

	std::vector<Drawables::Sprite> Pacman::_createMapFromVector(const std::vector<std::string> &map, int hOffset, int vOffset)
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

	Drawables::Rectangle Pacman::_getRectangleFromChar(char c, int xIndex, int yIndex)
	{
		Drawables::Rectangle rect;

		switch (c) {
		case MapChar::WALL:
			rect.x = xIndex * mapTileLength;
			rect.y = yIndex * mapTileLength;
			rect.endX = rect.x + mapTileLength;
			rect.endY = rect.y + mapTileLength;
			rect.color = mapWallColor;
			return rect;
		case MapChar::HIDE_RECTANGLE:
			rect.x = xIndex * mapTileLength;
			rect.y = (yIndex - 3) * mapTileLength;
			rect.endX = rect.x + mapTileLength;
			rect.endY = rect.y + (4 * mapTileLength);
			rect.color = 0x000000FF;
			return rect;
		case MapChar::BIG_PACGUM:
			rect.x = (xIndex * mapTileLength) + 1;
			rect.y = (yIndex * mapTileLength) + 1;
			rect.endX = rect.x + mapTileLength - 2;
			rect.endY = rect.y + mapTileLength - 2;
			rect.color = 0xFFFFFFFF;
			return rect;
		case MapChar::SMALL_PACGUM:
			rect.x = (xIndex * mapTileLength) + 1;
			rect.y = (yIndex * mapTileLength) + 1;
			rect.endX = rect.x + mapTileLength - 2;
			rect.endY = rect.y + mapTileLength - 2;
			rect.color = 0x777777FF;
			return rect;
		case MapChar::BLINKY:
			rect.x = xIndex * mapTileLength + 1;
			rect.y = yIndex * mapTileLength + 1;
			rect.endX = rect.x + mapTileLength - 2;
			rect.endY = rect.y + mapTileLength - 2;
			rect.color = 0xFF0000FF;
			return rect;
		case MapChar::INKY:
			rect.x = xIndex * mapTileLength + 1;
			rect.y = yIndex * mapTileLength + 1;
			rect.endX = rect.x + mapTileLength - 2;
			rect.endY = rect.y + mapTileLength - 2;
			rect.color = 0x00FFFFFF;
			return rect;
		case MapChar::CLYDE:
			rect.x = xIndex * mapTileLength + 1;
			rect.y = yIndex * mapTileLength + 1;
			rect.endX = rect.x + mapTileLength - 2;
			rect.endY = rect.y + mapTileLength - 2;
			rect.color = 0xFFB851FF;
			return rect;
		default: throw WrongMapChar(c);
		}
	}

	bool Pacman::_collideWithWallMap(int x, int y, int w, int h)
	{
		for (const auto &i : this->_map) {
			try {
				auto rect = dynamic_cast<Drawables::Rectangle &>(*i.fallback);
				if (rect.color != mapWallColor)
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

	Drawables::Sprite Pacman::_getSpriteFromChar(char c, int xIndex, int yIndex)
	{
		Drawables::Sprite ret;

		switch (c) {
		case MapChar::WALL:
			ret.fallback = std::make_shared<Drawables::Rectangle>(this->_getRectangleFromChar(c, xIndex, yIndex));
			return ret;
		case MapChar::HIDE_RECTANGLE:
			ret.fallback = std::make_shared<Drawables::Rectangle>(this->_getRectangleFromChar(c, xIndex, yIndex));
			return ret;
		case MapChar::BIG_PACGUM:
			ret.sizeY = mapTileLength;
			ret.sizeX = mapTileLength;
			ret.x = (xIndex * mapTileLength) + (ret.sizeX / 2);
			ret.y = (yIndex * mapTileLength) + (ret.sizeY / 2);
			ret.path = largePacgumFilename;
			ret.rotation = 0;
			ret.fallback = std::make_shared<Drawables::Circle>(this->_getCircleFromChar(c, xIndex, yIndex));
			ret.color = 0;
			return ret;
		case MapChar::SMALL_PACGUM:
			ret.sizeY = mapTileLength;
			ret.sizeX = mapTileLength;
			ret.x = (xIndex * mapTileLength) + (ret.sizeX / 2);
			ret.y = (yIndex * mapTileLength) + (ret.sizeY / 2);
			ret.path = smallPacgumFilename;
			ret.rotation = 0;
			ret.fallback = std::make_shared<Drawables::Circle>(this->_getCircleFromChar(c, xIndex, yIndex));
			ret.color = 0;
			return ret;
		case MapChar::BLINKY:
			ret.sizeY = mapTileLength;
			ret.sizeX = mapTileLength;
			ret.x = (xIndex * mapTileLength) + (ret.sizeX / 2);
			ret.y = (yIndex * mapTileLength) + (ret.sizeY / 2);
			ret.path = "assets/pacman/blinky.png";
			ret.rotation = 0;
			ret.fallback = std::make_shared<Drawables::Rectangle>(this->_getRectangleFromChar(c, xIndex, yIndex));
			ret.color = 0xFF0000FF;
			return ret;
		case MapChar::INKY:
			ret.sizeY = mapTileLength;
			ret.sizeX = mapTileLength;
			ret.x = (xIndex * mapTileLength) + (ret.sizeX / 2);
			ret.y = (yIndex * mapTileLength) + (ret.sizeY / 2);
			ret.path = "assets/pacman/inky.png";
			ret.rotation = 0;
			ret.fallback = std::make_shared<Drawables::Rectangle>(this->_getRectangleFromChar(c, xIndex, yIndex));
			ret.color = 0x00FFFFFF;
			return ret;
		case MapChar::CLYDE:
			ret.sizeY = mapTileLength;
			ret.sizeX = mapTileLength;
			ret.x = (xIndex * mapTileLength) + (ret.sizeX / 2);
			ret.y = (yIndex * mapTileLength) + (ret.sizeY / 2);
			ret.path = "assets/pacman/clyde.png";
			ret.rotation = 0;
			ret.fallback = std::make_shared<Drawables::Rectangle>(this->_getRectangleFromChar(c, xIndex, yIndex));
			ret.color = 0xFFB851FF;
			return ret;
		default: throw WrongMapChar(c);
		}
	}

	std::vector<Drawables::Sprite>::iterator Pacman::_collideWithPacgumMap(int x, int y, int w, int h)
	{
		int index = -1;

		for (const auto &sprite : this->_map) {
			index++;
			try {
				if (sprite.path != largePacgumFilename && sprite.path != smallPacgumFilename)
					continue;
				if (x + w <= sprite.x - sprite.sizeX / 2
				    || y + h <= sprite.y - sprite.sizeY / 2
				    || sprite.x + sprite.sizeX / 2  <= x
				    || sprite.y + sprite.sizeY / 2 <= y) {
					continue;
				}
				return this->_map.begin() + index;
			} catch (const std::bad_cast &) { }
		}
		return this->_map.end();
	}

	void Pacman::_processPlayerMovement(unsigned int ticks)
	{
		double newX;
		double newY;
		int &moveX = this->_playerMovement.first;
		int &moveY = this->_playerMovement.second;

		if (this->_moves.moveX) {
			moveX = this->_moves.moveX;
		} else if (!this->_moves.moveX && this->_moves.moveY) {
			moveY = this->_moves.moveY;
		}
		newX = this->pacmanSpeed * moveX * ticks;
		newY = this->pacmanSpeed * moveY * ticks;

		if (newX) {
			if (this->_collideWithWallMap(newX + this->_playerPosition.first - (this->_playerDrawable.sizeX / 2),
			                              this->_playerPosition.second - (this->_playerDrawable.sizeY / 2),
			                              this->_playerDrawable.sizeX,
			                              this->_playerDrawable.sizeY)) {
				moveX = 0;
				newX = 0;
			}
			this->_playerPosition.first += newX;
		}
		if (newY) {
			if (this->_collideWithWallMap(this->_playerPosition.first - (this->_playerDrawable.sizeX / 2),
			                              newY + this->_playerPosition.second - (this->_playerDrawable.sizeY / 2),
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

		// Teleportation
		if (moveX < 0 && this->_playerPosition.first < (mapOffsetTileX + 2) * mapTileLength) {
			this->_playerPosition.first = 23 * mapTileLength - (mapTileLength / 2);
		}
		if (moveX > 0 && this->_playerPosition.first > (23 + mapOffsetTileX - 2) * mapTileLength) {
			this->_playerPosition.first = (mapOffsetTileX + 1) * mapTileLength + (mapTileLength / 2);
		}
	}

	void Pacman::_processScore()
	{
		auto it = this->_collideWithPacgumMap(this->_playerPosition.first - (this->_playerDrawable.sizeX / 2),
		                                      this->_playerPosition.second - (this->_playerDrawable.sizeY / 2),
		                                      this->_playerDrawable.sizeX,
		                                      this->_playerDrawable.sizeY);
		if (it != this->_map.end()) {
			this->_gameScore += (*it).path == this->largePacgumFilename ? 50 : 10;
			this->_map.erase(it);
		}

		this->_scoreDrawable.text = "Score: " + std::to_string(this->_gameScore);
	}

	Drawables::Circle Pacman::_getCircleFromChar(char c, int xIndex, int yIndex)
	{
		Drawables::Circle ret;

		switch (c) {
		case MapChar::BIG_PACGUM:
			ret.size = 1;
			ret.x = (xIndex * mapTileLength) + (mapTileLength / 2.);
			ret.y = (yIndex * mapTileLength) + (mapTileLength / 2.);
			ret.fallback = std::make_shared<Drawables::Rectangle>(this->_getRectangleFromChar(c, xIndex, yIndex));
			ret.color = 0xFFFFFFFF;
			return ret;
		case MapChar::SMALL_PACGUM:
			ret.size = 1;
			ret.x = (xIndex * mapTileLength) + (mapTileLength / 2.);
			ret.y = (yIndex * mapTileLength) + (mapTileLength / 2.);
			ret.fallback = std::make_shared<Drawables::Rectangle>(this->_getRectangleFromChar(c, xIndex, yIndex));
			ret.color = 0x777777FF;
			return ret;
		default: throw WrongMapChar(c);
		}
	}
}

extern "C" Arcade::ModInfo getHeader()
{
	Arcade::ModInfo info;
	info.name = "Pacman";
	info.type = Arcade::ModInfo::GAME;
	info.magicNumber = Arcade::MagicNumber;
	return info;
}

extern "C" Arcade::IModule *getModule()
{
	return new Arcade::Pacman::Pacman;
}