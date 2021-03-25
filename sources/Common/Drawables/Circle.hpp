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
	//! @brief A circle game objecct.
	class Circle : public ADrawable
	{
	public:
		//! @brief The size of this circle (in percentage)
		unsigned size;

		//! @brief Default constructor
		Circle() = default;
		//! @brief Default copy constructor
		Circle(const Circle &) = default;
		//! @brief Default destructor
		~Circle() = default;
		//! @brief Default assignement operator
		Circle &operator=(const Circle &) = default;
	};
}
