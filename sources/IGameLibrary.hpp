/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** IGameLibrary
*/

#pragma once

#include "LibInfo.hpp"

namespace Arcade
{
	class IGameModule
	{
	public:
		//! @brief Virtual destructor
		virtual ~IGameModule() = default;

		//! @brief Get the library's header.
		//! @info Used to verify the integrity of the lib.
		virtual LibInfo getHeader() const = 0;

		//! @brief Initialize this library. (Create windows & so on)
		//! @return True if the initialization was successfull. False otherwise.
		virtual bool init() = 0;
	};
}