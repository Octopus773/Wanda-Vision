//
// Created by Zoe Roux on 3/29/21.
//

#include "Qix.hpp"

namespace Arcade::Qix
{
	bool Qix::init()
	{
		return false;
	}

	bool Qix::close()
	{
		return false;
	}

	bool Qix::shouldClose()
	{
		return false;
	}

	ModInfo::Modtype Qix::getType() const
	{
		return ModInfo::GAME;
	}

	const std::vector<std::string> &Qix::getSprites() const
	{

	}

	const std::vector<std::unique_ptr<ADrawable>> &Qix::getDrawables()
	{

	}

	void Qix::addTicks(unsigned int tick)
	{

	}

	void Qix::restart()
	{

	}

	void Qix::handleEvent(Event &event)
	{

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