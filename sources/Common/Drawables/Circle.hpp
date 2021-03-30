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
	struct Circle : public ADrawable
	{
		//! @brief The size of this circle (in percentage)
		unsigned size;
	};
}
