/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** GameObject
*/

#pragma once

#include <memory>

namespace Arcade::Drawables
{
	//! @brief A base struct for every objects in the game.
	struct ADrawable
	{
		//! @brief Get the X position of this object
		//! @info A percentage representing the position. 0 is left, 100 right.
		int x;

		//! @brief Get the Y position of this object
		//! @info A percentage representing the position. 0 is top, 100 bottom.
		int y;
		
		//! @brief The color of this object.
		//! @info color format is RRGGBBAA, 1 byte for each
		unsigned color;

		//! @brief Drawable to use if the renderer can't display the current object (can be nullptr).
		std::unique_ptr<ADrawable> fallback;

		//! @brief Default constructor
		ADrawable() = default;
		//! @brief Deleted copy constructor
		ADrawable(const ADrawable &) = delete;
		//! @brief Default move operator (needed because the unique_ptr set it as deleted)
		ADrawable(ADrawable &&move) = default;
		//! @brief Default destructor
		virtual ~ADrawable() = default;
		//! @brief Deleted assignment operator
		ADrawable &operator=(const ADrawable &) = delete;
	};
}
