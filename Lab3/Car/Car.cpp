#include <iostream>
#include <string>
#include "CRemoteControl.h"
#include "CCar.h"

int main()
{
	CCar car;
	CRemoteControl remoteControl(car, std::cin, std::cout);

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