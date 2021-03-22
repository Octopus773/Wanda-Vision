//
// Created by Zoe Roux on 3/22/21.
//

#pragma once

#include <string>
#include <vector>
#include <Common/IGameModule.hpp>
#include <memory>
#include <Common/IDisplayModule.hpp>
#include "Common/ModInfo.hpp"

namespace Arcade::Core
{
	class Runner
	{
	private:
		//! @brief A list of available games
		std::vector<ModInfo> _games;
		//! @brief A list of available renderers
		std::vector<ModInfo> _graphs;
		//! @brief The current game instance
		std::unique_ptr<IGameModule> _game;
		//! @brief The current renderer instance
		std::unique_ptr<IDisplayModule> _renderer;
	public:
		//! @brief Set this runner's game library.
		void setGame(const std::string &path);
		//! @brief Set this runner's graphical library.
		void setRenderer(const std::string &path);
		//! @brief List game libraries
		std::vector<ModInfo> getGames() const;
		//! @brief List graphial libraries
		std::vector<ModInfo> getRenderers() const;

		int runParser();

		//! @brief Default constructor
		Runner() = default;
		//! @brief Constructor that sets a graphical library.
		explicit Runner(const std::string &graphicLib);
		//! @brief Default copy constructor
		Runner(const Runner &) = default;
		//! @brief Default destructor
		~Runner() = default;
		//! @brief Default  assignment operator
		Runner &operator=(const Runner &) = default;
	};
}