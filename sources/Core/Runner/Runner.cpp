//
// Created by Zoe Roux on 3/22/21.
//

#include <filesystem>
#include <Exceptions/InvalidLibraryException.hpp>
#include <Exceptions/InvalidArgumentException.hpp>
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

	int Runner::runShell()
	{
		return 0;
	}

	int Runner::runGame()
	{
		return 0;
	}
}