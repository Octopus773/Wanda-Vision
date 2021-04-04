//
// Created by cbihan on 4/4/21.
//

#pragma once

#include <stdexcept>

namespace Arcade
{
	class WrongMapChar : public std::runtime_error
	{
	public:
		//! @brief Constructor with a message.
		explicit WrongMapChar(char c)
			: std::runtime_error("Got unknown map char " + std::to_string(c)) {}
		//! @brief Default copy constructor
		WrongMapChar(const WrongMapChar &) = default;
		//! @brief Default destructor
		~WrongMapChar() override = default;
	};
}