//
// Created by Zoe Roux on 3/22/21.
//

#include <iostream>
#include "Core/Runner/Runner.hpp"

using namespace Arcade::Core;

int usage(char *bin)
{
	std::cout << "Usage: " << bin << " [GraphicLib]" << std::endl;
	return 84;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return usage(argv[0]);
	try {
		Runner runner(argv[1])
		return runner.runShell();
	} catch(const std::exception &ex) {
		std::cerr << ex.what() << std::endl;
		return 84;
	}
}
