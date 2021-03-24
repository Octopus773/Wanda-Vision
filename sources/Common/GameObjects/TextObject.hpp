/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** GameObject
*/

#pragma once

#include "Common/GameObject.hpp"
#include <string>

namespace Arcade::GameObjects
{
	//! @brief A text object.
	class TextObject : public GameObject
	{
	public:
		//! @brief The text to display
		std::string text;

		//! @brief Default constructor
		TextObject() = default;
		//! @brief Default copy constructor
		TextObject(const TextObject &) = default;
		//! @brief Default destructor
		~TextObject() = default;
		//! @brief Default assignement operator
		TextObject &operator=(const TextObject &) = default;
	};
}
