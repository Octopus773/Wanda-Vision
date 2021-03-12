/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** IDisplayLibrary
*/

#pragma once

#include "LibInfo.hpp"

namespace Arcade
{
	class IDisplayModule
	{
	public:
		//! @brief Virtual destructror
		virtual ~IDisplayModule() = default;

		//! @brief Get the library's header.
		//! @info Used to verify the integrity of the lib.
		virtual struct LibInfo getHeader() = 0;

		//! @brief Initialize this library. (Create windows & so on)
		//! @return True if the initialization was successfull. False otherwise.
		virtual bool init() = 0;
	};
}