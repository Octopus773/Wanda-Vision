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
	class Text : public ADrawable
	{
	public:
		//! @brief The text to display
		std::string text;
		//! @brief The size of the text to display
		unsigned fontSize;
		//! @brief The font file 
		std::string path;

		//! @brief Default constructor
		Text() = default;
		//! @brief Default copy constructor
		Text(const Text &) = default;
		//! @brief Default destructor
		~Text() = default;
		//! @brief Default assignement operator
		Text &operator=(const Text &) = default;
	};
}
