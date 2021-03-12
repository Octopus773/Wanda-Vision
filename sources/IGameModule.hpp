/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** IGameLibrary
*/

#pragma once

#include "ModInfo.hpp"
#include "GameObject.hpp"
#include <vector>

namespace Arcade
{
	//! @brief The interface of all games.
	class IGameModule
	{
	public:
		//! @brief Virtual destructor
		virtual ~IGameModule() = default;

		//! @brief Get the library's header.
		//! @info Used to verify the integrity of the lib.
		virtual ModInfo getHeader() const = 0;

		//! @brief Return a list of game objects to display.
		//! @return The list of objects
		virtual std::vector<GameObject> getObjects() = 0;
	};
}