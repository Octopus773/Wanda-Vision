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
		this->createDrawablesFromVector({
			                                "wwwwwwwwwwwwwwwwwww",
			                                "w    w       w    w",
			                                "w ww w wwwww w ww w",
			                                "  w             w w",
			                                "w w ww ww ww ww w w",
			                                "w      w   w      w",
			                                "w w ww ww ww ww w w",
			                                "  w             w w",
			                                "w ww w wwwww w ww w",
			                                "w    w       w    w",
			                                "wwwwwwwwwwwwwwwwwww",
		                                }, 0, 0);
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
		//this->_drawables.clear();
	/*	this->_playerDrawable.x = this->_playerPosition.first;
		this->_playerDrawable.y = this->_playerPosition.second;
		//this->_playerDrawable.fallback->x = this->_playerPosition.first - 5;
		//this->_playerDrawable.fallback->y = this->_playerPosition.second - 5;
		if (auto fallback = dynamic_cast<Drawables::Rectangle *>(this->_playerDrawable.fallback.get())) {
			fallback->endX = fallback->x + 5;
			fallback->endY = fallback->y + 5;
		}
		this->_drawables.push_back(std::make_unique<Drawables::Sprite>(this->_playerDrawable)); */
		return this->_drawables;
	}

	const std::vector<Sound> &Pacman::getSounds()
	{
		return this->_sounds;
	}

	void Pacman::addTicks(unsigned int tick)
	{
		this->_resources.clear();
	}

	void Pacman::restart()
	{

	}

	void Pacman::handleEvent(Event &event)
	{
		try {
			auto key = dynamic_cast<Events::KeyboardEvent &>(event);
			switch (key.key) {
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

	void Pacman::createDrawablesFromVector(const std::vector<std::string> &map, int hOffset, int vOffset)
	{
		int xIndex = 0;
		int yIndex = 0;

		for (const auto &i : map) {
			for (const auto &j : i) {
				if (j == ' ') {
					continue;
				}
				this->_drawables.emplace_back(this->getDrawableFromChar(j, xIndex, yIndex));
				this->_drawables.back()->x += hOffset;
				this->_drawables.back()->y += vOffset;
				xIndex++;
			}
			xIndex = 0;
			yIndex++;
		}
	}

	std::unique_ptr<Drawables::ADrawable> Pacman::getDrawableFromChar(char c, int xIndex, int yIndex)
	{
		Drawables::Rectangle rect;

		switch (c) {
		case 'w':
			rect.x = xIndex * mapTileLength;
			rect.y = yIndex * mapTileLength;
			rect.endX = rect.x + mapTileLength;
			rect.endY = rect.y + mapTileLength;
			std::cout << "x:" << rect.x << " y: " << rect.y << " ex: " << rect.endX << " ey: " << rect.endY << std::endl;
			rect.color = 0x0033FFFF + rand();
			return std::make_unique<Drawables::Rectangle>(rect);
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