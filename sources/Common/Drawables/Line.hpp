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
	//! @brief A base class for every objects in the game.
	class Line : public ADrawable
	{
	public:
		//! @brief Get the end X position of the line
		//! @info A percentage representing the position. 0 is left, 100 right.
		int endX;
		//! @brief Get the end Y position of the line
		//! @info A percentage representing the position. 0 is top, 100 bottom.
		int endY;

		//! @brief Default constructor
		Line() = default;
		//! @brief Default copy constructor
		Line(const Line &) = default;
		//! @brief Default destructor
		~Line() = default;
		//! @brief Default assignement operator
		Line &operator=(const Line &) = default;
	};
}
