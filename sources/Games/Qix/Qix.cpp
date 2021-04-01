//
// Created by Zoe Roux on 3/29/21.
//

#include <Common/Drawables/Circle.hpp>
#include <Common/Drawables/Rectangle.hpp>
#include "Qix.hpp"
#include "Common/Events/KeyBoardEvent.hpp"

namespace Arcade::Qix
{
	bool Qix::init()
	{
		this->_playerDrawable = Drawables::Circle();
		this->_playerDrawable.size = 1;
		this->_playerDrawable.color = 0xFF0000FF;
		Drawables::Rectangle fallback;
		fallback.color = 0xFF0000FF;
		this->_playerDrawable.fallback = std::make_unique<Drawables::Rectangle>(fallback);
		return true;
	}

	bool Qix::close()
	{
		return true;
	}

	bool Qix::shouldClose()
	{
		return false;
	}

	ModInfo::Modtype Qix::getType() const
	{
		return ModInfo::GAME;
	}

	const std::vector<std::pair<std::string, std::string>> &Qix::getResources() const
	{
		return this->_resources;
	}

	const std::vector<std::unique_ptr<Drawables::ADrawable>> &Qix::getDrawables()
	{
		this->_drawables.clear();
		this->_playerDrawable.x = this->_playerPosition.first;
		this->_playerDrawable.y = this->_playerPosition.second;
		this->_playerDrawable.fallback->x = this->_playerPosition.first - 5;
		this->_playerDrawable.fallback->y = this->_playerPosition.second - 5;
		if (auto fallback = dynamic_cast<Drawables::Rectangle *>(this->_playerDrawable.fallback.get())) {
			fallback->endX = fallback->x + 5;
			fallback->endY = fallback->y + 5;
		}
		this->_drawables.push_back(std::make_unique<Drawables::ADrawable>(this->_playerDrawable));
		return this->_drawables;
	}

	const std::vector<Sound> &Qix::getSounds()
	{
		return this->_sounds;
	}

	void Qix::addTicks(unsigned int tick)
	{
		if (this->_drawType == None)
			this->_drawType = this->_moves.draw;
		double moveSpeed = this->_moveSpeeds[this->_drawType];

		this->_playerPosition.first += moveSpeed * this->_moves.moveX * tick;
		this->_playerPosition.second += moveSpeed * this->_moves.moveY * tick;
	}

	void Qix::restart()
	{

	}

	void Qix::handleEvent(Event &event)
	{
		try {
			auto key = dynamic_cast<Events::KeyboardEvent &>(event);
			if (key.type == Event::KeyUp)
				return;
			if (key.type == Event::KeyDown) {
				if (key.key == Events::KeyboardEvent::CTRL)
					this->_moves.draw = Slow;
				if (key.key == Events::KeyboardEvent::SPACE)
					this->_moves.draw = Fast;
				return;
			}
			switch (key.key) {
			case Events::KeyboardEvent::UP_ARROW:
			case Events::KeyboardEvent::KEY_Z:
				this->_moves.moveY = std::min(1, this->_moves.moveY + 1);
				break;
			case Events::KeyboardEvent::DOWN_ARROW:
			case Events::KeyboardEvent::KEY_S:
				this->_moves.moveY = std::max(-1, this->_moves.moveY - 1);
				break;
			case Events::KeyboardEvent::RIGHT_ARROW:
			case Events::KeyboardEvent::KEY_Q:
				this->_moves.moveX = std::min(1, this->_moves.moveX + 1);
				break;
			case Events::KeyboardEvent::LEFT_ARROW:
			case Events::KeyboardEvent::KEY_D:
				this->_moves.moveX = std::max(-1, this->_moves.moveX - 1);
				break;
			default:
				return;
			}
		}
		catch (const std::bad_cast &) { }
	}

	unsigned long Qix::getScore()
	{
		return 0;
	}
}

extern "C" Arcade::ModInfo getHeader()
{
	Arcade::ModInfo info;
	info.name = "Qix";
	info.type = Arcade::ModInfo::GAME;
	info.magicNumber = Arcade::MagicNumber;
	return info;
}

extern "C" Arcade::IModule *getModule()
{
	return new Arcade::Qix::Qix;
}