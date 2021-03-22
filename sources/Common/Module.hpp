/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Library
*/

#pragma once

#include "ModInfo.hpp"

namespace Arcade
{

	//! @brief A base module interface
	class IModule {
	public:
		//! @brief Virtual destructor
		virtual ~IModule() = default;

		//! @brief Initialize this library. (Create windows & so on)
		//! @return True if the initialization was successful. False otherwise.
		virtual bool init() = 0;

		//! @brief Allow to say to the library  t shutdown and free it's content
		//! @return True if the shutdown was successful. False otherwise.
		virtual bool close() = 0;

		//! @brief Should this module be closed?
		//! @return True if this module should be closed. False otherwise.
		virtual bool shouldClose() = 0;
	};
}

//! @brief Get the library's header.
//! @info Used to verify the integrity of the lib.
extern "C" struct Arcade::ModInfo getHeader();

//! @brief Get the module class.
//! @return A new instance of a IDisplayModule or IGameModule.
extern "C" Arcade::IModule *getModule();