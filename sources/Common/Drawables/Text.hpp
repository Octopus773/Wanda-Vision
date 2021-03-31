/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** GameObject
*/

#pragma once

#include "Common/Drawables/ADrawable.hpp"
#include <string>

namespace Arcade::Drawables
{
	//! @brief A text object.
	struct Text : public ADrawable
	{
		//! @brief The text to display
		std::string text;
		//! @brief The size of the text to display
		unsigned fontSize;
		//! @brief The font file 
		std::string path;
	};
}
