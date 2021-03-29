/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** GameObject
*/

#pragma once

#include "Common/Drawables/ADrawable.hpp"

namespace Arcade::Drawables
{
	//! @brief A rectangle object.
	class Rectangle : public ADrawable
	{
	public:
		//! @brief Get the end X position of the line
		//! @info A percentage representing the position. 0 is left, 100 right.
		int endX;
		//! @brief Get the end Y position of the line
		//! @info A percentage representing the position. 0 is top, 100 bottom.
		int endY;

		//! @brief Default constructor
		Rectangle() = default;
		//! @brief Default copy constructor
		Rectangle(const Rectangle &) = default;
		//! @brief Default destructor
		~Rectangle() = default;
		//! @brief Default assignement operator
		Rectangle &operator=(const Rectangle &) = default;
	};
}
