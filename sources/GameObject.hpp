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
	class GameObject
	{
	public:
		//! @brief Get the X position of this object
		//! @return A percentage representing the position. 0 is left, 100 right.
		int getX() const;

		//! @brief Get the Y position of this object
		//! @return A percentage representing the position. 0 is top, 100 bottom.
		int getY() const;

		//! @brief Default constructor
		GameObject() = default;
		//! @brief Default copy constructor
		GameObject(const GameObject &) = default;
		//! @brief Default destructor
		~GameObject() = default;
		//! @brief Default assignement operator
		GameObject &operator=(const GameObject &) = default;
	};
}