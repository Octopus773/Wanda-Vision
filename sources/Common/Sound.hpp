/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Sound
*/

#pragma once

#include <string>

namespace Arcade
{
	struct Sound
	{
		//! @brief The path to the sound to play
		std::string path;

		//! @brief Should this sound loop?
		bool loop;

		//! @brief Should playing this sound stop others sounds
		bool stopOthers;
	};
}