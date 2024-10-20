/*
* This program describes dynamic linking with project MyTestLibrary.
* Dynamic linking can be executed on load or in runtime.
* Runtime linking can be turned on by setting _runtime define to 1,
* load linking - setting _runtime to 0.
*/

#include <iostream>

// This define can be 0 or 1
// 0 will be considered as using load dynamic linking
// 1 will be considered as using runtime dynamic linking
#define _runtime 1

#include "loadlib.h"

int main()
{
	std::cout << "This program calculates square root of inputted value.\n";

	// Region of loading module, which depends on _runtime define value
#pragma region Load

	const char* module_name = "MyTestLibrary.dll";
	
	sqrtfunc_ptr my_sqrt;

#if _runtime
	std::cout << "Program runs in dynamic linking runtime mode.\n\n";
	my_sqrt = loadlib(module_name);
#else
	std::cout << "Program runs in dynamic linking startup mode.\n\n";
	my_sqrt = ::my_sqrt;
#endif


	if (my_sqrt == nullptr)
	{
		std::cerr << "Could not load module " << module_name << std::endl;
		return -1;
	}
	
	std::cout << "Loaded module " << module_name << std::endl;

#pragma endregion Load

	// Program itself, calculates square root
	double value;
	std::cout << "Enter your value:\n";
	std::cin >> value;
	
	double result = my_sqrt(value);
	std::cout << "Square root of " << value << " is ";

	if (result == -1)
	{
		std::cout << "undefined";
	}
	else
	{
		std::cout << result;
	}

	std::cout << std::endl;

#if _runtime
	if (!freelib(module_name))
	{
		std::cout << "Error unloading library" << module_name << std::endl;
		return -1;
	}
#endif

	return 0;
}