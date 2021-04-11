#include <iostream>
#include <string>
#include "CRemoteControl.h"
#include "CCalculator.h"

int main()
{
	CCalculator calc;
	CRemoteControl remoteControl(calc, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!remoteControl.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
	return 0;
}