//
// Created by Zoe Roux on 3/22/21.
//


#pragma once

#include <stdexcept>

namespace Arcade
{
	class InvalidArgumentException : public std::invalid_argument
	{
	public:
		//! @brief Constructor with a message.
		explicit InvalidArgumentException(const std::string &str)
			: std::invalid_argument(str) {}
		//! @brief Default copy constructor
		InvalidArgumentException(const InvalidArgumentException &) = default;
		//! @brief Default destructor
		~InvalidArgumentException() override = default;
	};
}