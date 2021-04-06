//
// Created by cbihan on 4/6/21.
//

#pragma once

#include <stdexcept>

namespace Arcade
{
	class ResourceCreationFailure : public std::runtime_error
	{
	public:
		//! @brief Constructor with a message.
		explicit ResourceCreationFailure(const std::string &str)
			: std::runtime_error(str) {}
		//! @brief Default copy constructor
		ResourceCreationFailure(const ResourceCreationFailure &) = default;
		//! @brief Default destructor
		~ResourceCreationFailure() override = default;
	};
}