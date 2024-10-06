#include <iostream>

int sum(int* address, int size)
{
	int sum = 0;

	for (int i = 0; i < size; i++)
	{
		sum += address[i];
	}

	return sum;
}

int main()
{
	int* arr = new int[10] {1, -10, 2, 15, 8, -4, -2, 9, 11, 0 };

	std::cout << "Sum of elements equal to " << sum(arr, 10) << std::endl;
	return 0;
}