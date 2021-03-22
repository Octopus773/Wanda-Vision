//
// Created by Zoe Roux on 3/22/21.
//

#include <iostream>
#include "sources/Core/Runner.hpp"

using namespace Arcade::Core;

int usage(char *bin)
{
	std::cout << "Usage: " << bin << " [GraphicLib]" << std::endl;
	return 2;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return usage(argv[0]);
	Runner runner(argv[1]);
	return runner.StartShell();
}