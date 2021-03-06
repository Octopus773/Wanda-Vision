//
// Created by Zoe Roux on 3/22/21.
//

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include <fstream>
#include "Common/IGameModule.hpp"
#include "Common/IDisplayModule.hpp"
#include "Core/Library.hpp"
#include "Common/ModInfo.hpp"

namespace Arcade::Core
{
	//! @brief Core class to run libs and games.
	class Runner
	{
	private:
		//! @brief A list of available games
		std::vector<Library> _games;
		//! @brief A list of available renderers
		std::vector<Library> _renderers;
		//! @brief The current game instance
		std::unique_ptr<IGameModule> _game;
		//! @brief The current renderer instance
		std::unique_ptr<IDisplayModule> _renderer;

		//! @brief Draw an object with the current renderer.
		void _drawObject(Drawables::ADrawable *obj);
		//! @brief Handle a single event (short handle it if this is a runner event or sent it to the game)
		bool _handleEvent(const std::unique_ptr<Event> &event);

		//! @brief The currently loaded game index.
		int _gameIndex = 0;
		//! @brief The currently loaded renderer index.
		int _rendererIndex = 0;

		//! @brief Save scores of the current game.
		void _saveScore();
	public:
		//! @brief Score by game and by player.
		//! @info format: <game, <username, score>>.
		std::map<std::string, std::map<std::string, unsigned long>> scores;

		//! @brief Set this runner's game library.
		void setGame(Library &lib);
		//! @brief Get the current renderer
		const Library &getRenderer() const;
		//! @brief Set this runner's game library using the path.
		void setGame(std::string path);
		//! @brief Set this runner's graphical library.
		void setRenderer(Library &lib);
		//! @brief Set this runner's graphical library using the path.
		void setRenderer(std::string path);
		//! @brief List game libraries
		std::vector<Library> &getGames();
		//! @brief List renderers libraries
		std::vector<Library> &getRenderers();

		//! @brief The name of the current user.
		std::string username = "USERNAME";

		//! @brief run the game.
		//! @return The return status of the game
		int runGame();

		//! @brief Run the shell.
		//! @return The return status of the shell.
		int runShell();

		//! @brief Remove the current game and use the menu instead.
		void setShell();

		//! @brief Load available libraries from the path
		void loadLibraries(const std::string &path);

		//! @brief Default constructor
		Runner();
		//! @brief Constructor that sets a graphical library.
		explicit Runner(const std::string &graphicLib);
		//! @brief Deleted copy constructor
		Runner(const Runner &) = delete;
		//! @brief Custom destructor
		~Runner();
		//! @brief Deleted assignment operator
		Runner &operator=(const Runner &) = delete;
	};
}