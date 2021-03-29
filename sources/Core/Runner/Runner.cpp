//
// Created by Zoe Roux on 3/22/21.
//

#include <filesystem>
#include "Exceptions/InvalidLibraryException.hpp"
#include "Exceptions/InvalidArgumentException.hpp"
#include "Common/Events/KeyBoardEvent.hpp"
#include "Runner.hpp"

namespace Arcade::Core
{
	Runner::Runner()
	{
		this->loadLibraries("./lib");
	}

	Runner::Runner(const std::string &graphicLib)
	{
		this->loadLibraries("./lib");
		auto lib = std::find_if(this->_renderers.begin(), this->_renderers.end(), [&graphicLib](Library &x) {
			return x.path == graphicLib;
		});
		if (lib == this->_renderers.end())
			throw InvalidArgumentException("Renderer library not found.");
		this->setRenderer(*lib);
	}

	void Runner::loadLibraries(const std::string &path)
	{
		for (auto &item : std::filesystem::directory_iterator(path)) {
			Library library(item.path());
			if (library.info.type == ModInfo::GAME)
				this->_games.push_back(std::move(library));
			else if (library.info.type == ModInfo::GRAPHIC)
				this->_renderers.push_back(std::move(library));
			else
				throw InvalidLibraryException("Invalid library type.");
		}
	}

	const std::vector<Library> &Runner::getGames() const
	{
		return this->_games;
	}

	const std::vector<Library> &Runner::getRenderers() const
	{
		return this->_renderers;
	}

	void Runner::setRenderer(Library &lib)
	{
		if (lib.info.type != ModInfo::GRAPHIC)
			throw std::invalid_argument("Can't use a non renderer as a renderer.");
		this->_renderer = lib.start<IDisplayModule>();
	}

	void Runner::setGame(Library &lib)
	{
		if (lib.info.type != ModInfo::GAME)
			throw std::invalid_argument("Can't use a non game as a game.");
		this->_game = lib.start<IGameModule>();
	}

	void Runner::_drawObject(const std::unique_ptr<ADrawable> &obj)
	{
		bool ret = false;

		if (auto sprite = dynamic_cast<Drawables::Sprite *>(obj.get()))
			ret = this->_renderer->draw(*sprite);
		if (auto rec = dynamic_cast<Drawables::Rectangle *>(obj.get()))
			ret = this->_renderer->draw(*rec);
		if (auto circle = dynamic_cast<Drawables::Circle *>(obj.get()))
			ret = this->_renderer->draw(*circle);
		if (auto line = dynamic_cast<Drawables::Line *>(obj.get()))
			ret = this->_renderer->draw(*line);
		if (auto text = dynamic_cast<Drawables::Text *>(obj.get()))
			ret = this->_renderer->draw(*text);
		if (ret)
			return;
		if (obj->fallback)
			this->_drawObject(obj->fallback);
		throw std::runtime_error("Unknown game object time met. Aborting...");
	}

	void Runner::_handleEvent(const std::unique_ptr<Event> &event)
	{
		if (auto key = dynamic_cast<Events::KeyboardEvent *>(event.get())) {
			// TODO handle local keys here
			return;
		}
		this->_game->handleEvent(*event);
	}

	int Runner::runShell()
	{
		return 0;
	}

	int Runner::runGame()
	{
		auto timer = std::chrono::steady_clock::now();
		while (!this->_game->shouldClose()) {
			for (auto &event : this->_renderer->pullEvents())
				this->_handleEvent(event);
			for (auto &obj : this->_game->getDrawables())
				this->_drawObject(obj);
			this->_renderer->refresh();
			auto newTimer = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(newTimer - timer).count();
			this->_game->addTicks(duration);
			timer = newTimer;
		}
		// TODO handle scores here.
		return 0;
	}
}