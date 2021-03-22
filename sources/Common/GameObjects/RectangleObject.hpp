/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** GameObject
*/

#pragma once

#include "GameObject.hpp"

namespace Arcade::GameObjects
{
	//! @brief A rectangle object.
	class RectangleObject : public GameObject
	{
	public:
		//! @brief Get the end X position of the line
		//! @info A percentage representing the position. 0 is left, 100 right.
		int endX;
		//! @brief Get the end Y position of the line
		//! @info A percentage representing the position. 0 is left, 100 right.
		int endY;

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
