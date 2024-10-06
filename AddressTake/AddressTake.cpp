#include <iostream>
#include <string>

int main()
{
	int a;
	
	std::cout << "Enter your value: ";
	std::cin >> a;

	std::cout << "\nValue entered is " << a << "\n";
	std::cout << "\nAddress of this value is " << &a << "\n\n";
	std::cout << "\nWaiting for next move..." << std::endl;
	
	while (1);

	return 0;
}