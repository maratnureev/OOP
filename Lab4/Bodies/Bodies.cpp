#include <iostream>
#include <string>
#include "BodiesController.h"

int main()
{
	BodiesController bodiesController(std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!bodiesController.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
	return 0;
}