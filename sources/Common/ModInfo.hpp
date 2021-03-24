/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** LibInfo
*/

#pragma once

#include <string>

namespace Arcade
{
	//! @brief The header of every libraries
	struct ModInfo
	{
		enum Modtype {
			GAME,
			GRAPHIC
		};

		//! @brief A number used to check if this lib belong to the project or if it is a garbage lib.
		long magicNumber = 0xBA0BAB;
		//! @brief The type of this library.
		Modtype type;
		//! @brief The name of this library.
		std::string name;
	};
}