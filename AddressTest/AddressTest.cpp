#include <iostream>
#include <string>
#include <windows.h>

int main()
{
	int a;
	std::cout << "Random stack address: " << &a << "\n";

	std::cout << "Enter your address:\n";
	
	std::string address_str;
	std::cin >> address_str;

	if (address_str.substr(0, 2) == "0x")
	{
		unsigned long long address = 0;

		for (int i = 2; i < address_str.size(); i++)
		{
			char val = address_str[i], offset = 0;
			
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
				else goto err;
			}

			address = (address << 4) + offset;
		}

		int* address_of_smth = reinterpret_cast<int*>(address);

		std::cout << "Given address is " << address_of_smth << "\n";

		if (IsBadReadPtr(address_of_smth, sizeof(int)))
		{
			std::cerr << "There is no access to this memory for current process\n" << std::endl;
		}
		else
		{
			int something = *address_of_smth;
			std::cout << "Value stored this address is " << something << std::endl;
		}
	}
	else
	{
		err:
		std::cerr << "Entered value does not represent an address." << std::endl;
		return -1;
	}

	return 0;
}