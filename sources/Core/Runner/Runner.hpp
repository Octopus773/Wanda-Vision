//
// Created by Zoe Roux on 3/22/21.
//

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <functional>
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
		bool _drawObject(const std::unique_ptr<ADrawable> &obj);
		//! @brief Handle a single event (short handle it if this is a runner event or sent it to the game)
		void _handleEvent(const std::unique_ptr<Event> &event);
	public:
		//! @brief Set this runner's game library.
		void setGame(Library &lib);
		//! @brief Set this runner's graphical library.
		void setRenderer(Library &lib);
		//! @brief List game libraries
		const std::vector<Library> &getGames() const;
		//! @brief List renderers libraries
		const std::vector<Library> &getRenderers() const;

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
		//! @brief Deleted copy constructor
		Runner(const Runner &) = delete;
		//! @brief Default destructor
		~Runner() = default;
		//! @brief Deleted assignment operator
		Runner &operator=(const Runner &) = delete;
	};
}