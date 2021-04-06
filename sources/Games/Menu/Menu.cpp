//
// Created by Zoe Roux on 2021-04-05.
//

#include <Common/Events/KeyBoardEvent.hpp>
#include <Common/Events/MouseClickEvent.hpp>
#include "Menu.hpp"

namespace Arcade::Menu
{
	Menu::Menu(Core::Runner &runner)
		: _runner(runner)
	{ }

	bool Menu::init()
	{
		this->_resources.emplace_back("font", "assets/roboto.ttf");

		Drawables::Text title;
		title.path = "assets/roboto.ttf";
		title.x = 10;
		title.y = 5;
		title.color = 0xFFFFFFFF;
		title.fontSize = 16;
		title.text = "Games (BestScore)";
		this->_drawables.emplace_back(std::make_unique<Drawables::Text>(title));
		title.x = 60;
		title.text = "Renderers";
		this->_drawables.emplace_back(std::make_unique<Drawables::Text>(title));
		int i = 0;
		for (auto &lib : this->_runner.getGames()) {
			Drawables::Text text;
			text.path = "assets/roboto.ttf";
			text.x = 10;
			text.y = 20 + i * 10;
			text.color = 0xFFFFFFFF;
			text.fontSize = 13;
			text.text = lib.info.name + " (" + std::to_string(this->_runner.scores[lib.info.name][this->_runner.username]) + ")";
			this->_drawables.emplace_back(std::make_unique<Drawables::Text>(text));
			i++;
		}
		i = 0;
		for (auto &lib : this->_runner.getRenderers()) {
			Drawables::Text text;
			text.path = "assets/roboto.ttf";
			text.x = 60;
			text.y = 20 + i * 10;
			text.color = lib == this->_runner.getRenderer() ? 0xff6e00ff : 0xFFFFFFFF;
			text.fontSize = 13;
			text.text = lib.info.name;
			this->_drawables.emplace_back(std::make_unique<Drawables::Text>(text));
			i++;
		}

		Drawables::Line line;
		line.x = 50;
		line.endX = 50;
		line.y = 0;
		line.endY = 85;
		line.color = 0xFFFFFFFF;
		this->_drawables.emplace_back(std::make_unique<Drawables::Line>(line));
		line.x = 0;
		line.endX = 100;
		line.y = 15;
		line.endY = 15;
		this->_drawables.emplace_back(std::make_unique<Drawables::Line>(line));

		title.text = "Username";
		title.x = 48;
		title.y = 90;
		this->_drawables.emplace_back(std::make_unique<Drawables::Text>(title));
		return true;
	}

	bool Menu::close()
	{
		return true;
	}

	void Menu::addTicks(unsigned int) { }

	const std::vector<std::unique_ptr<Drawables::ADrawable>> &Menu::getDrawables()
	{
		if (auto txt = dynamic_cast<Drawables::Text *>(this->_drawables.back().get()))
			txt->text= this->_runner.username;
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
		return this->_shouldClose;
	}

	const std::vector<Sound> &Menu::getSounds()
	{
		return this->_sounds;
	}

	void Menu::handleEvent(Event &event)
	{
		if (auto key = dynamic_cast<Events::KeyboardEvent *>(&event)) {
			if (key->key == Events::KeyboardEvent::ESCAPE)
				this->_shouldClose = true;
			if (key->type == Event::KeyUp)
				return;
			if (key->key == Events::KeyboardEvent::BACKSPACE)
				this->_runner.username = this->_runner.username.substr(0, this->_runner.username.size() - 1);
			if (isalpha(key->key))
				this->_runner.username += static_cast<char>(key->key);
		}
		if (auto key = dynamic_cast<Events::MouseClickEvent *>(&event)) {
			if (key->button != Events::MouseClickEvent::LEFT)
				return;
			int idx = (key->y - 20) / 10;
			if (key->x <= 50 && idx >= 0 && this->_runner.getGames().size() > idx)
				this->_runner.setGame(this->_runner.getGames()[idx]);
			if (key->x > 50 && idx >= 0 && this->_runner.getRenderers().size() > idx)
				this->_runner.setRenderer(this->_runner.getRenderers()[idx]);
		}
	}

	void Menu::restart() { }

	ModInfo::Modtype Menu::getType() const
	{
		return ModInfo::GAME;
	}
}