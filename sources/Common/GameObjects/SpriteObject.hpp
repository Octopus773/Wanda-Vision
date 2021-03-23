/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** SpriteObject
*/

#pragma once

#include "Common/GameObject.hpp"
#include <string>

namespace Arcade::GameObjects
{
	//! @brief A Sprite game objecct.
	class SpriteObject : public GameObject
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
		//! @brief GameObject to use if the renderer can't display sprites.
		GameObject &fallback;

		//! @brief Default constructor
		SpriteObject() = default;
		//! @brief Default copy constructor
		SpriteObject(const SpriteObject &) = default;
		//! @brief Default destructor
		~SpriteObject() = default;
		//! @brief Default assignement operator
		SpriteObject &operator=(const SpriteObject &) = default;
	};
}
