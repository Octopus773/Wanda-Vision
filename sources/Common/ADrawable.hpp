/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** GameObject
*/

#pragma once

namespace Arcade
{
	//! @brief A base class for every objects in the game.
	class ADrawable
	{
	public:
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

		//! @brief Default destructor
		virtual ~ADrawable() = default;
		//! @brief Default assignement operator
		ADrawable &operator=(const ADrawable &) = default;
	protected:
		//! @brief Default constructor (protected because the class is abstract)
		ADrawable() = default;
		//! @brief Default copy constructor (protected because the class is abstract)
		ADrawable(const ADrawable &) = default;
	};
}
