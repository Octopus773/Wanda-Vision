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

namespace Arcade::Pacman
{
	bool Pacman::init()
	{
	/*	Drawables::Rectangle rect;

		rect.x = 5;
		rect.y = 5;
		rect.endY = 50;
		rect.endX = 2;
		rect.color = 0x33FFFFF;*/
		//this->_drawables.emplace_back(std::make_unique<Drawables::Rectangle>(rect));
		this->_map = this->createMapFromVector({
			                                       "wwwwwwwwwwwwwwwwwww",
			                                       "wP   w       w    w",
			                                       "w ww w wwwww w ww w",
			                                       "  w             w w",
			                                       "w w ww ww ww ww w w",
			                                       "w      w   w      w",
			                                       "w w ww wwwww ww w w",
			                                       "  w             w w",
			                                       "w ww w wwwww w ww w",
			                                       "w    w       w    w",
			                                       "wwwwwwwww wwwwwwwww",
		                                       }, 0, 0);

		this->_resources.emplace_back(std::make_pair("sprite", "resources/pacman.png"));
		this->_playerDrawable = Drawables::Sprite();
		this->_playerDrawable.sizeY = 5;
		this->_playerDrawable.sizeX = 5;
		this->_playerDrawable.color = 0;
		this->_playerDrawable.rotation = 0;
		this->_playerDrawable.x = 50;
		this->_playerDrawable.y = 50;
		this->_playerDrawable.path = "resources/pacman.png";
		Drawables::Line fallback;
		fallback.x = 90;
		fallback.y = 10;
		fallback.endX = 10;
		fallback.endY = 90;
		fallback.color = 0xFF00FFFF;
		return true;
	}

	bool Pacman::close()
	{
		return true;
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
	/*	//this->_playerDrawable.fallback->x = this->_playerPosition.first - 5;
		//this->_playerDrawable.fallback->y = this->_playerPosition.second - 5;
		if (auto fallback = dynamic_cast<Drawables::Rectangle *>(this->_playerDrawable.fallback.get())) {
			fallback->endX = fallback->x + 5;
			fallback->endY = fallback->y + 5;
		}*/
		for (const auto &i : this->_map) {
			this->_drawables.emplace_back(std::make_unique<Drawables::Sprite>(i));
		}
		this->_drawables.push_back(std::make_unique<Drawables::Sprite>(this->_playerDrawable));
		return this->_drawables;
	}

	const std::vector<Sound> &Pacman::getSounds()
	{
		return this->_sounds;
	}

	void Pacman::addTicks(unsigned int tick)
	{
		static double newX = 0;
		static double newY = 0;
		static int saveMoveX = 0;
		static int saveMoveY = 0;

		this->_resources.clear();
		if (this->_moves.moveX) {
			saveMoveX = this->_moves.moveX;
		} else if (!this->_moves.moveX && this->_moves.moveY) {
			saveMoveY = this->_moves.moveY;
		}

		newX = .000025 * saveMoveX * tick;
		newY = .000025 * saveMoveY * tick;

		if (newX) {
		    if (this->collideWithMap(newX + this->_playerPosition.first - (this->_playerDrawable.sizeX / 2),
							            this->_playerPosition.second - (this->_playerDrawable.sizeY / 2),
							            this->_playerDrawable.sizeX,
							            this->_playerDrawable.sizeY)) {
		    	saveMoveX = 0;
		    	newX = 0;
		    }
			this->_playerPosition.first += newX;
		}
		if (newY) {
			if (this->collideWithMap(this->_playerPosition.first - (this->_playerDrawable.sizeX / 2),
			                         newY + this->_playerPosition.second - (this->_playerDrawable.sizeY / 2),
			                         this->_playerDrawable.sizeX,
			                         this->_playerDrawable.sizeY)) {
				saveMoveY = 0;
				newY = 0;
			}
			this->_playerPosition.second += newY;
		}
		this->_moves.moveX = 0;
		this->_moves.moveY = 0;
	}

	void Pacman::restart()
	{

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
		return 0;
	}

	std::vector<Drawables::Sprite> Pacman::createMapFromVector(const std::vector<std::string> &map, int hOffset, int vOffset)
	{
		std::vector<Drawables::Sprite> ret;
		int xIndex = -1;
		int yIndex = -1;

		for (const auto &i : map) {
			yIndex++;
			xIndex = -1;
			for (const auto &j : i) {
				xIndex++;
				if (j == ' ') {
					continue;
				}
				ret.emplace_back(this->getSpriteFromChar(j, xIndex, yIndex));
				ret.back().x += hOffset;
				ret.back().y += vOffset;
			}
		}
		return ret;
	}

	Drawables::Rectangle Pacman::getRectangleFromChar(char c, int xIndex, int yIndex)
	{
		Drawables::Rectangle rect;

		switch (c) {
		case 'w':
			rect.x = xIndex * mapTileLength;
			rect.y = yIndex * mapTileLength;
			rect.endX = rect.x + mapTileLength;
			rect.endY = rect.y + mapTileLength;
			rect.color = mapWallColor;
			return rect;
		case 'P':
			rect.x = (xIndex * mapTileLength) + 2;
			rect.y = (yIndex * mapTileLength) + 2;
			rect.endX = rect.x + mapTileLength - 4;
			rect.endY = rect.y + mapTileLength - 4;
			rect.color = 0xFFFFFFFF;
			return rect;
		default: throw WrongMapChar(c);
		}
	}

	bool Pacman::collideWithMap(int x, int y, int w, int h)
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

	Drawables::Sprite Pacman::getSpriteFromChar(char c, int xIndex, int yIndex)
	{
		Drawables::Sprite ret;

		switch (c) {
		case 'w':
			ret.fallback = std::make_shared<Drawables::Rectangle>(this->getRectangleFromChar(c, xIndex, yIndex));
			return ret;
		case 'P':
			ret.sizeY = 25;
			ret.sizeX = 25;
			ret.x = (xIndex * mapTileLength) + (ret.sizeX / 2);
			ret.y = (yIndex * mapTileLength) + (ret.sizeY / 2);
			ret.path = "ressources/large_pacgum.png";
			ret.rotation = 0;
			ret.fallback = std::make_shared<Drawables::Rectangle>(this->getRectangleFromChar('P', xIndex, yIndex));
			ret.color = 0;
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