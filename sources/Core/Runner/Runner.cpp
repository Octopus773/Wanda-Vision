//
// Created by Zoe Roux on 3/22/21.
//

#include <filesystem>
#include <Exceptions/InvalidLibraryException.hpp>
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
			Library library(item.path());
			if (library.info.type == ModInfo::GAME)
				this->_games.push_back(library);
			else if (library.info.type == ModInfo::GRAPHIC)
				this->_renderers.push_back(library);
			else
				throw InvalidLibraryException("Invalid library type.");
		}
	}

	std::vector<Library> Runner::getGames() const
	{
		return this->_games;
	}

	std::vector<Library> Runner::getRenderers() const
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