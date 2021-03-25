//
// Created by Zoe Roux on 3/22/21.
//


#pragma once

#include "Common/Module.hpp"
#include "Common/ModInfo.hpp"
#include "Exceptions/InvalidLibraryException.hpp"
#include <memory>
#include <dlfcn.h>

namespace Arcade::Core
{
	//! @brief A struct representing a library
	struct Library
	{
	private:
		//! @brief dlopen handle.
		void *_handle;
	public:
		//! @brief The path of this library.
		std::string path;
		//! @brief Information about this library.
		ModInfo info;
		//! @brief Initialize the library and get the functions.
		template<typename T>
		std::unique_ptr<T> start()
		{
			auto module = reinterpret_cast<T *(*)()>(dlsym(this->_handle, "getModule"));
			if (!module)
				throw InvalidLibraryException("No getModule function found in the library.");
			auto value = module();
			if (!value)
				throw InvalidLibraryException("Invalid module returned.");
			value->init();
			return std::unique_ptr<T>(value);
		}

		//! @brief Load a library from a path.
		explicit Library(const std::string &path);
		//! @brief No copy constructor
		Library(const Library &) = delete;
		//! @brief A move constructor
		Library(Library &&) noexcept;
		//! @brief Destructor that close the library.
		~Library();
		//! @brief No assignment operator.
		Library &operator=(const Library &) = delete;
	};
}