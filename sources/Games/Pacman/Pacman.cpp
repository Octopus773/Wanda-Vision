//
// Created by Zoe Roux on 3/29/21.
//

#include "Common/Drawables/Circle.hpp"
#include "Common/Drawables/Rectangle.hpp"
#include "Common/Drawables/Sprite.hpp"
#include "Common/Drawables/Text.hpp"
#include "Common/Drawables/Line.hpp"
#include "Pacman.hpp"
#include "Common/Events/KeyBoardEvent.hpp"

namespace Arcade::Pacman
{
	bool Pacman::init()
	{
		this->_resources.emplace_back(std::make_pair("font", "resources/angelina.ttf"));
		this->_resources.emplace_back(std::make_pair("sprite", "resources/pacman.png"));
		this->_playerDrawable = Drawables::Sprite();
		this->_playerDrawable.sizeY = 20;
		this->_playerDrawable.sizeX = 20;
		this->_playerDrawable.color = 0;
		this->_playerDrawable.rotation = 0;
		this->_playerDrawable.path = "resources/pacman.png";
		Drawables::Line fallback;
		fallback.x = 90;
		fallback.y = 10;
		fallback.endX = 10;
		fallback.endY = 90;
		fallback.color = 0xFF00FFFF;
		/*Drawables::Circle fallback;
		fallback.color = 0xFFFF00FF;
		fallback.size = 5;*/
		this->_playerDrawable.fallback = std::make_unique<Drawables::Line>(fallback);

		// create the map
		Drawables::Rectangle rec1;

		rec1.x = 5;
		rec1.y = 10;
		rec1.endX = 95;
		rec1.endY = rec1.y + 9;
		rec1.color = 0x0000FFFF;

		this->map.emplace_back(rec1);
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
		//this->_playerDrawable.fallback->x = this->_playerPosition.first - 5;
		//this->_playerDrawable.fallback->y = this->_playerPosition.second - 5;
		if (auto fallback = dynamic_cast<Drawables::Rectangle *>(this->_playerDrawable.fallback.get())) {
			fallback->endX = fallback->x + 5;
			fallback->endY = fallback->y + 5;
		}
		this->_drawables.push_back(std::make_unique<Drawables::Sprite>(this->_playerDrawable));
		for (const auto &rec : this->map) {
			this->_drawables.push_back(std::make_unique<Drawables::Rectangle>(rec));
		}
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