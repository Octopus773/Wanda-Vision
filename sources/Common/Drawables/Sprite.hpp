/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** SpriteObject
*/

#pragma once

#include "Common/ADrawable.hpp"
#include <string>

namespace Arcade::Drawables
{
	//! @brief A Sprite game objecct.
	class Sprite : public ADrawable
	{
	public:
		//! @brief The size of this sprite (percentage in X)
		unsigned int sizeX;
		//! @brief The size of this sprite (percentage in Y)
		unsigned int sizeY;
		//! @brief number between 0 and 360 clock wise
		unsigned short rotation;
		//! @brief Path of the sprite to display (this should be cached by the renderer).
		std::string path;

		//! @brief Default constructor
		Sprite() = default;
		//! @brief Default copy constructor
		Sprite(const Sprite &) = default;
		//! @brief Default destructor
		~Sprite() = default;
		//! @brief Default assignement operator
		Sprite &operator=(const Sprite &) = default;
	};
}
