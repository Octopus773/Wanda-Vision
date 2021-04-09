//
// Created by Zoe Roux on 3/22/21.
//

#include <filesystem>
#include "Library.hpp"

namespace Arcade::Core
{
	Library::Library(const std::string &path)
		: path(path), _handle(dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL))
	{
		if (!this->_handle) {
			throw InvalidLibraryException(dlerror());
		}
		auto header = reinterpret_cast<ModInfo *(*)()>(dlsym(this->_handle, "getHeader"));
		if (!header)
			throw InvalidLibraryException(dlerror());
		auto value = header();
		if (!value || value->magicNumber != MagicNumber)
			throw InvalidLibraryException("Invalid header returned.");
		this->info = *value;
	}

	Library::~Library()
	{
		if (this->_handle)
			dlclose(this->_handle);
	}

	Library::Library(Library &&other) noexcept
		: _handle(other._handle), path(other.path), info(other.info)
	{
		other._handle = nullptr;
	}

	bool Library::operator==(const Library &x) const
	{
		return std::filesystem::path(x.path) == std::filesystem::path(this->path);
	}

	bool Library::operator!=(const Library &x) const
	{
		return !this->operator==(x);
	}
}
