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
	//! @brief A base class for every objects in the game.
	class LineObject : public GameObject
	{
	public:
		//! @brief Get the end X position of the line
		//! @info A percentage representing the position. 0 is left, 100 right.
		int endX;
		//! @brief Get the end Y position of the line
		//! @info A percentage representing the position. 0 is left, 100 right.
		int endY;

		//! @brief Default constructor
		LineObject() = default;
		//! @brief Default copy constructor
		LineObject(const LineObject &) = default;
		//! @brief Default destructor
		~LineObject() = default;
		//! @brief Default assignement operator
		LineObject &operator=(const LineObject &) = default;
	};
}
