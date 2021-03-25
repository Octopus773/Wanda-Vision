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
	//! @brief The magic number used to check if the lib is a valid one.
	constexpr long MagicNumber = 0xBA0BAB;

	//! @brief The header of every libraries
	struct ModInfo
	{
		enum Modtype {
			UNDEFINED,
			GAME,
			GRAPHIC
		};

		//! @brief A number used to check if this lib belong to the project or if it is a garbage lib.
		long magicNumber = MagicNumber;
		//! @brief The type of this library.
		Modtype type;
		//! @brief The name of this library.
		std::string name;
	};
}