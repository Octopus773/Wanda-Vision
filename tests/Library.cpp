//
// Created by Zoe Roux on 2021-04-09.
//

#include <criterion/criterion.h>
#include <Core/Library.hpp>

using namespace Arcade;
using namespace Arcade::Core;

Test(library, open)
{
	Library lib("./lib/arcade_pacman.so");
	cr_assert_eq(lib.info.name, "Pacman");
}

Test(library, open_badlib)
{
	cr_assert_throw(Library lib("./lib"), InvalidLibraryException);
}