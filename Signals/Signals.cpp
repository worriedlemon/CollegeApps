#include <iostream>
#include <signal.h>

/*
* One of the simpler IPC methods is to use signals. Processes
* can pass signals between each other. There are many types of
* signals in UNIX, although there are no signals in Windows,
* except for SIGINT, SIGTERM, SIGALRM, SIGABRT and some others.
* 
* This simple app redefines behavior of the signal SIGINT,
* which is passed when process get Ctrl+C input to interrupt
* its execution.
* 
* This app is written for Windows operating system
*/

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