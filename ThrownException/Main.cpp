#include <iostream>
#include <stdexcept>
#include <conio.h>

/*
* Program for generating exception which causes OS
* (Windows system) to create a dump in event journal
*/

int main()
{
	std::cout << "Press any key to generate exception...\n";
	{
		// Waiting for an input
		auto _ = _getch();
	}
	std::cerr << "Generating exception..." << std::endl;

	// Starting event viewer to catch a dump
	system("eventvwr");
	
	// Not catching on purpose, so Windows event viewer can make error dump
	throw std::logic_error("Something went wrong!");

	return 0;
}