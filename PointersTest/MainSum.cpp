/*
* A project, demonstrating derefernce of a pointer, which
* contains logical address to the memory cell, where the
* information is being stored. Pointers are used to pass
* big blocks of data (e.g. arrays) between functions.
* 
* In this simple case, an array with random integers is
* passed in the `sum` function, which returns agregated
* sum of elements in the array.
*/

#include <iostream>

int sum(int* address, int size)
{
	int sum = 0;

	// Calculating sum of elements
	for (int i = 0; i < size; i++)
	{
		// To shift an address left by `i` type sizes in bytes we use instruction `address + i`
		// To dereference a pointer we use unary operator `*`, so to get i-th element
		// `*(address + i)` should be used
		// 
		// Using square brackets (`address[i]`) is equal to `*(address + i)`
		sum += address[i];
	}

	return sum;
}

int main()
{
	// Using `new` to create a memory block in dynamic memory (heap)
	int* arr = new int[10] {1, -10, 2, 15, 8, -4, -2, 9, 11, 0 };

	std::cout << "Sum of elements equal to " << sum(arr, 10) << std::endl;

	// Remember to free allocated memory
	delete[] arr;
	return 0;
}