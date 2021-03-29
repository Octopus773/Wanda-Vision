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
	struct Rectangle : public ADrawable
	{
		//! @brief Get the end X position of the line
		//! @info A percentage representing the position. 0 is left, 100 right.
		int endX;
		//! @brief Get the end Y position of the line
		//! @info A percentage representing the position. 0 is left, 100 right.
		int endY;
	};
}
