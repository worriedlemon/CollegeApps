#include <iostream>
#include <signal.h>

// Creating custom SIGINT signal handler
void signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		// Write something to a console
		std::cout << "\nNOOOO, I'm being interrupted!\nGoodbye then..." << std::endl;
		_exit(SIGINT);
	}
}

int main()
{
	std::cout << "I am process with redefined behavior of signal SIGINT!\n";
	// Override SIGINT signal handling with custom function
	signal(SIGINT, signal_handler);

	char option[256];
	while (true)
	{
		// Some gibberish to demonstrate Ctrl+C event
		std::cin >> option;

		if (option[1] == '\0' && option[0] == '0')
		{
			break;
		}
	}

	return 0;
}