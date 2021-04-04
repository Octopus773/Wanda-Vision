//
// Created by Zoe Roux on 3/22/21.
//

#include <filesystem>
#include <iostream>
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
		this->setRenderer(graphicLib);
	}

	void Runner::loadLibraries(const std::string &path)
	{
		for (auto &item : std::filesystem::directory_iterator(path)) {
			try {
				Library library(item.path());
				if (library.info.type == ModInfo::GAME)
					this->_games.push_back(std::move(library));
				else if (library.info.type == ModInfo::GRAPHIC)
					this->_renderers.push_back(std::move(library));
			} catch (const InvalidLibraryException &ex) {
				std::cerr << "Invalid library found: " << ex.what() << std::endl;
				continue;
			}
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

	void Runner::setRenderer(const std::string &path)
	{
		auto lib = std::find_if(this->_renderers.begin(), this->_renderers.end(), [&path](Library &x) {
			return std::filesystem::path(x.path) == std::filesystem::path(path);
		});
		if (lib == this->_renderers.end())
			throw InvalidArgumentException("Renderer library not found.");
		this->setRenderer(*lib);
	}

	void Runner::setGame(Library &lib)
	{
		if (lib.info.type != ModInfo::GAME)
			throw std::invalid_argument("Can't use a non game as a game.");
		this->_game = lib.start<IGameModule>();
	}

	void Runner::setGame(const std::string &path)
	{
		auto lib = std::find_if(this->_games.begin(), this->_games.end(), [&path](Library &x) {
			return std::filesystem::path(x.path) == std::filesystem::path(path);
		});
		if (lib == this->_games.end())
			throw InvalidArgumentException("Game library not found.");
		this->setGame(*lib);
	}

	void Runner::_drawObject(Drawables::ADrawable *obj)
	{
		bool ret = false;

		if (auto sprite = dynamic_cast<Drawables::Sprite *>(obj))
			ret = this->_renderer->draw(*sprite);
		if (auto rec = dynamic_cast<Drawables::Rectangle *>(obj))
			ret = this->_renderer->draw(*rec);
		if (auto circle = dynamic_cast<Drawables::Circle *>(obj))
			ret = this->_renderer->draw(*circle);
		if (auto line = dynamic_cast<Drawables::Line *>(obj))
			ret = this->_renderer->draw(*line);
		if (auto text = dynamic_cast<Drawables::Text *>(obj))
			ret = this->_renderer->draw(*text);
		if (ret)
			return;
		if (obj->fallback)
			return this->_drawObject(obj->fallback.get());
		throw std::runtime_error("Unknown game object time met. Aborting...");
	}

	bool Runner::_handleEvent(const std::unique_ptr<Event> &event)
	{
		if (event->type == Event::Close)
			return true;
		if (auto key = dynamic_cast<Events::KeyboardEvent *>(event.get())) {
			// TODO handle local keys here
			//return false;
		}
		this->_game->handleEvent(*event);
		return false;
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
				if (this->_handleEvent(event))
					return 0;
			for (auto &resource : this->_game->getResources())
				this->_renderer->load(resource.first, resource.second);
			for (auto &obj : this->_game->getDrawables())
				this->_drawObject(obj.get());
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