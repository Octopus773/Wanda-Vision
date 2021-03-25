//
// Created by Zoe Roux on 3/22/21.
//


#pragma once

#include <stdexcept>

namespace Arcade
{
	class InvalidLibraryException : public std::invalid_argument
	{
	public:
		//! @brief Constructor with a message.
		explicit InvalidLibraryException(const std::string &str)
			: std::invalid_argument(str) {}
		//! @brief Default copy constructor
		InvalidLibraryException(const InvalidLibraryException &) = default;
		//! @brief Default destructor
		~InvalidLibraryException() override = default;
	};
}