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
	//! @brief A circle game objecct.
	class CircleObject : public GameObject
	{
	public:
		//! @brief The size of this circle (in percentage)
		unsigned size;

		//! @brief Default constructor
		CircleObject() = default;
		//! @brief Default copy constructor
		CircleObject(const CircleObject &) = default;
		//! @brief Default destructor
		~CircleObject() = default;
		//! @brief Default assignement operator
		CircleObject &operator=(const CircleObject &) = default;
	};
}
