#include <iostream>
#include <string>
#include <windows.h>

/*
* This program converts input string into address. Then this address
* is being dereferenced (or allocated first), user writes random data
* and program tries to print the value stored at this address.
*/

typedef unsigned long long uint64;

// Function to convert string to address
uint64 get_address_from_str(std::string& str)
{
	uint64 address = 0i64;

	// If address starts with `0x` it is also valid
	char index;
	if (str.substr(0, 2) == "0x")
	{
		index = 2;
	}
	else index = 0;

	for (; index < str.size(); index++)
	{
		// Taking a symbol
		char val = str[index], offset = 0;

		// Depending on a symbol, converting it from a hexadecimal number to decimal (case insensitive)
		switch (val)
		{
		case 'a':
		case 'A':
			offset = 10; break;
		case 'b':
		case 'B':
			offset = 11; break;
		case 'c':
		case 'C':
			offset = 12; break;
		case 'd':
		case 'D':
			offset = 13; break;
		case 'e':
		case 'E':
			offset = 14; break;
		case 'f':
		case 'F':
			offset = 15; break;
		default:
			if (val >= '0' && val <= '9')
			{
				offset = (val - '0');
			}
			else
			{
				// If values are not in range [0-9,A-F], this string is not valid
				std::cerr << "Value given does not represent an address!" << std::endl;
				return NULL;
			}
		}

		// Getting address
		address = (address << 4) + offset;
	}

	return address;
}

int main()
{
	// Example of an address
	int a = 42;
	std::cout << "Example of an address in stack: " << &a << "\n";

	std::cout << "\nEnter your desired address:\n";
	
	// String, which contains address
	std::string address_str;
	std::cin >> address_str;

	// Reinterpreting obtained integer as some address in memory
	int* address_of_smth = reinterpret_cast<int*>(get_address_from_str(address_str));
	if (address_of_smth == nullptr)
	{
		return -1;
	}

	std::cout << "Given address is " << address_of_smth << "\n";

	// Checking pointer for read access
	bool bad_pointer = IsBadReadPtr(address_of_smth, sizeof(int));
	if (bad_pointer)
	{
		// If address has no read access, try to allocate virtual memory at it
		address_of_smth = reinterpret_cast<int*>(VirtualAlloc(address_of_smth, sizeof(int), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));

		std::cout << "Real address is " << address_of_smth << "\n";
		if (address_of_smth == nullptr)
		{
			std::cerr << "Address is inaccessible" << std::endl;
			return -1;
		}
	}

	// Enter some value
	std::cout << "Enter value to be stored:\n";
	std::cin >> *address_of_smth;

	// Check for stored value in cycle
	char cont;
	do
	{
		std::cout << "Value stored is " << *address_of_smth << "\n";
		std::cout << "Read again? [Y/N]\n";
		std::cin >> cont;
	}
	while (cont == 'Y' || cont == 'y');

	// Free virtual allocated memory if the pointer had no read access
	if (bad_pointer)
	{
		VirtualFree(reinterpret_cast<void *>(address_of_smth), 0, MEM_RELEASE);
	}

	return 0;
}