//
// Created by Zoe Roux on 3/22/21.
//

#include "Library.hpp"

namespace Arcade::Core
{
	Library::Library(const std::string &path)
		: path(path), _handle(dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL))
	{
		if (!this->_handle)
			throw InvalidLibraryException("Invalid library path.");
		auto header = reinterpret_cast<ModInfo *(*)()>(dlsym(this->_handle, "getHeader"));
		if (!header)
			throw InvalidLibraryException("No getHeader function found in the library.");
		auto value = header();
		if (!value || value->magicNumber != 0xBA0BAB)
			throw InvalidLibraryException("Invalid header returned.");
		this->info = *value;
	}

	Library::~Library()
	{
		dlclose(this->_handle);
	}

	Library::Library(Library &&other) noexcept
		: _handle(other._handle), path(other.path), info(other.info)
	{
		other._handle = nullptr;
	}
}
