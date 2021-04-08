//
// Created by Zoe Roux on 3/29/21.
//

#include <Common/Drawables/Circle.hpp>
#include <Common/Drawables/Rectangle.hpp>
#include <iostream>
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
		Drawables::Line line1;
		line1.x = 5;
		line1.y = 5;
		line1.endX = 95;
		line1.endY = 5;
		line1.color = 0xFFFFFFFF;
		this->_zones.push_back(line1);
		Drawables::Line line2;
		line2.x = 5;
		line2.y = 5;
		line2.endX = 5;
		line2.endY = 95;
		line2.color = 0xFFFFFFFF;
		this->_zones.push_back(line2);
		Drawables::Line line3;
		line3.x = 95;
		line3.y = 5;
		line3.endX = 95;
		line3.endY = 95;
		line3.color = 0xFFFFFFFF;
		this->_zones.push_back(line3);
		Drawables::Line line4;
		line4.x = 5;
		line4.y = 95;
		line4.endX = 95;
		line4.endY = 95;
		line4.color = 0xFFFFFFFF;
		this->_zones.push_back(line4);
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
		this->_playerDrawable.fallback->x = this->_playerPosition.first - 1;
		this->_playerDrawable.fallback->y = this->_playerPosition.second - 1;
		if (auto fallback = dynamic_cast<Drawables::Rectangle *>(this->_playerDrawable.fallback.get())) {
			fallback->endX = fallback->x + 1;
			fallback->endY = fallback->y + 1;
		}
		for (auto &shape : this->_zones)
			this->_drawables.push_back(std::make_unique<Drawables::Line>(shape));
		for (auto &shape : this->_lines)
			this->_drawables.push_back(std::make_unique<Drawables::Line>(shape));
		this->_drawables.push_back(std::make_unique<Drawables::Circle>(this->_playerDrawable));
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
		this->_moves.draw = None;
		double moveSpeed = this->_moveSpeeds[this->_drawType];

		double newX = this->_playerPosition.first + moveSpeed * this->_moves.moveX * tick;
		double newY = this->_playerPosition.second + moveSpeed * this->_moves.moveY * tick;
		bool canMoveX = std::any_of(this->_zones.begin(), this->_zones.end(), [this, newX](Drawables::Line &line) {
			if (line.y != line.endY)
				return false;
			if (line.y != static_cast<int>(this->_playerPosition.second))
				return false;
			return line.x <= static_cast<int>(newX) && static_cast<int>(newX) <= line.endX
				|| line.x >= static_cast<int>(newX) && static_cast<int>(newX) >= line.endX;
		});
		bool canMoveY = std::any_of(this->_zones.begin(), this->_zones.end(), [this, newY](Drawables::Line &line) {
			if (line.x != line.endX)
				return false;
			if (line.x != static_cast<int>(this->_playerPosition.first))
				return false;
			return line.y <= static_cast<int>(newY) && static_cast<int>(newY) <= line.endY
				|| line.y >= static_cast<int>(newY) && static_cast<int>(newY) >= line.endY;
		});

		if (this->_drawType == None) {
			if (canMoveX && canMoveY) {
				// TODO disable the canMove of the closed direction.
			}
			if (canMoveX)
				this->_playerPosition.first = newX;
			else if (canMoveY)
				this->_playerPosition.second = newY;
		}
		else {
			if (this->_lines.empty())
				this->_startLine();
			auto &current = this->_lines.back();

			if ((current.endX <= current.x && this->_moves.moveX == -1) || (current.endX >= current.x && this->_moves.moveX == 1))
				this->_playerPosition.first = newX;
			else if (this->_moves.moveX == 0
				&& (current.endY <= current.y && this->_moves.moveY == -1) || (current.endY >= current.y && this->_moves.moveY == 1))
				this->_playerPosition.second = newY;

			bool sameX = this->_moves.moveX != 0 && current.y != static_cast<int>(this->_playerPosition.second);
			bool sameY = this->_moves.moveY != 0 && current.x != static_cast<int>(this->_playerPosition.first);

			if (sameX || (this->_moves.moveX == 0 && sameY))
				this->_startLine();
			else {
				current.endX = static_cast<int>(this->_playerPosition.first);
				current.endY = static_cast<int>(this->_playerPosition.second);
			}

			if ((canMoveX || canMoveY)
				&& std::abs(current.endX - current.x) + std::abs(current.endY - current.y) > 2) {
				this->_drawType = None;
				this->_closeZone();
			}
		}
		this->_moves.moveX = 0;
		this->_moves.moveY = 0;
	}

	void Qix::_startLine()
	{
		Drawables::Line line;
		line.x = this->_playerPosition.first;
		line.y = this->_playerPosition.second;
		line.endX = this->_playerPosition.first;
		line.endY = this->_playerPosition.second;
		line.color = 0xFFFFFFFF;
		this->_lines.push_back(line);
	}

	void Qix::_closeZone()
	{
		std::move(this->_lines.begin(), this->_lines.end(), std::back_inserter(this->_zones));
		this->_lines.clear();
	}

	void Qix::restart()
	{
		this->_lines.clear();
		this->_zones.clear();
		this->_playerPosition = {50, 95};
		this->init();
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