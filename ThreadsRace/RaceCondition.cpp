#include <iostream>
#include <thread>

/*
* Program which demonstrates race condition of two threads
* executing same function with different argument
*/

// Procedure which is executed in other threads (shared 'cout' variable)
void foo(int index)
{
	for (int i = 0; i < 10; i++)
		std::cout << "Thread #" << index << "\n"; // These lines will be written out randomly
}

int main()
{
	// Creating two independent threads
	std::thread thr(foo, 1), thr2(foo, 2);

	// Waiting for them to finish
	thr.join(); thr2.join();

	return 0;
}