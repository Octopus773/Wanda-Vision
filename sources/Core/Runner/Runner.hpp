//
// Created by Zoe Roux on 3/22/21.
//

#pragma once

#include <string>
#include <vector>
#include <Common/IGameModule.hpp>
#include <memory>
#include <Common/IDisplayModule.hpp>
#include <Core/Library.hpp>
#include "Common/ModInfo.hpp"

namespace Arcade::Core
{
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
	public:
		//! @brief Set this runner's game library.
		void setGame(Library &lib);
		//! @brief Set this runner's graphical library.
		void setRenderer(Library &lib);
		//! @brief List game libraries
		std::vector<Library> getGames() const;
		//! @brief List renderers libraries
		std::vector<Library> getRenderers() const;

		//! @brief run the game.
		//! @return The return status of the game
		int runGame();

		//! @brief Run the shell.
		//! @return The return status of the shell.
		int runShell();

		//! @brief Load available libraries from the path
		void loadLibraries(const std::string &path);

		//! @brief Default constructor
		Runner();
		//! @brief Constructor that sets a graphical library.
		explicit Runner(const std::string &graphicLib);
		//! @brief Default copy constructor
		Runner(const Runner &) = delete;
		//! @brief Default destructor
		~Runner() = default;
		//! @brief Default  assignment operator
		Runner &operator=(const Runner &) = delete;
	};
}