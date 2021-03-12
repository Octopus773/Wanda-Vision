/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Library
*/

#pragma once

#include "ModInfo.hpp"

class IModule
{
public:
	//! @brief Virtual destructor
	virtual ~IModule() = default;

	//! @brief Initialize this library. (Create windows & so on)
	//! @return True if the initialization was successfull. False otherwise.
	virtual bool init() = 0;
};


//! @brief Get the library's header.
//! @info Used to verify the integrity of the lib.
extern "C" struct ModInfo getHeader();

//! @brief Get the module class.
//! @return A new instance of a IDisplayModule or IGameModule.
extern "C" IModule getModule();