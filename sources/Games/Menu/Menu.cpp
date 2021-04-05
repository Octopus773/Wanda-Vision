//
// Created by Zoe Roux on 2021-04-05.
//

#include "Menu.hpp"

namespace Arcade::Menu
{
	Menu::Menu(Core::Runner &runner)
		: _runner(runner)
	{ }

	bool Menu::init()
	{
		Drawables::Text title;
		title.x = 10;
		title.y = 10;
		title.color = 0xFFFFFFFF;
		title.fontSize = 16;
		title.text = "Games";
		this->_drawables.emplace_back(std::make_unique<Drawables::Text>(title));
		title.x = 60;
		title.text = "Renderers";
		this->_drawables.emplace_back(std::make_unique<Drawables::Text>(title));
		int i = 0;
		for (auto &lib : this->_runner.getGames()) {
			Drawables::Text text;
			text.x = 10;
			text.y = 20 + i * 10;
			text.color = 0xFFFFFFFF;
			text.fontSize = 13;
			text.text = lib.info.name;
			this->_drawables.emplace_back(std::make_unique<Drawables::Text>(text));
			i++;
		}
		i = 0;
		for (auto &lib : this->_runner.getRenderers()) {
			Drawables::Text text;
			text.x = 60;
			text.y = 20 + i * 10;
			text.color = lib == this->_runner.getRenderer() ? 0xff6e00 : 0xFFFFFFFF;
			text.fontSize = 13;
			text.text = lib.info.name;
			this->_drawables.emplace_back(std::make_unique<Drawables::Text>(text));
			i++;
		}

		Drawables::Line line;
		line.x = 50;
		line.endX = 50;
		line.y = 0;
		line.endY = 100;
		line.color = 0xFFFFFFFF;
		this->_drawables.emplace_back(std::make_unique<Drawables::Line>(line));
		line.x = 0;
		line.endX = 100;
		line.y = 15;
		line.endY = 15;
		this->_drawables.emplace_back(std::make_unique<Drawables::Line>(line));
		return true;
	}

	bool Menu::close()
	{
		return true;
	}

	void Menu::addTicks(unsigned int) { }

	const std::vector<std::unique_ptr<Drawables::ADrawable>> &Menu::getDrawables()
	{
		return this->_drawables;
	}

	const std::vector<std::pair<std::string, std::string>> &Menu::getResources() const
	{
		return this->_resources;
	}

	unsigned long Menu::getScore()
	{
		return 0;
	}

	bool Menu::shouldClose()
	{
		return false;
	}

	const std::vector<Sound> &Menu::getSounds()
	{
		return this->_sounds;
	}

	void Menu::handleEvent(Event &event)
	{

	}

	void Menu::restart() { }

	ModInfo::Modtype Menu::getType() const
	{
		return ModInfo::GAME;
	}
}