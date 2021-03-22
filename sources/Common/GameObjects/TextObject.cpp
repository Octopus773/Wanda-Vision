/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** GameObject
*/

#pragma once

#include "GameObject.hpp"
#include <string>

namespace Arcade::GameObjects
{
	//! @brief A rectangle object.
	class RectangleObject : public GameObject
	{
	public:
		//! @brief The text to display
		std::string text;

		//! @brief Default constructor
		RectangleObject() = default;
		//! @brief Default copy constructor
		RectangleObject(const RectangleObject &) = default;
		//! @brief Default destructor
		~RectangleObject() = default;
		//! @brief Default assignement operator
		RectangleObject &operator=(const RectangleObject &) = default;
	};
}
