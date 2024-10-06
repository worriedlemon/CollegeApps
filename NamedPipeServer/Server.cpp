#include <iostream>
#include <windows.h>

#define PIPE(name) TEXT("\\\\.\\pipe\\"##name)

typedef unsigned long int uint32;

constexpr wchar_t my_pipe_name[] = PIPE("my_pipe");

int main()
{
    char buffer[1024];

    const size_t bufferSize = sizeof(buffer);

    // Creating named pipe
	HANDLE pipe = CreateNamedPipeW(my_pipe_name,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        1,
        bufferSize,
        bufferSize,
        NMPWAIT_USE_DEFAULT_WAIT,
        nullptr);

    std::cout << "Waiting for connection...\n";

    // If pipe initialized correctly
    while (pipe != INVALID_HANDLE_VALUE)
    {
        // Waiting for a connection to a pipe
        if (ConnectNamedPipe(pipe, NULL))
        {
            std::cout << "Connection was received...\n";

            uint32 bytesRead;
            // Start reading data from pipe
            while (ReadFile(pipe, buffer, bufferSize - 1, &bytesRead, nullptr))
            {
                // Write received data in a console
                buffer[bytesRead] = '\0';
                std::cout << "Message received: " << buffer << "\n";
            }
        }

        // Destroy named pipe
        DisconnectNamedPipe(pipe);
    }

	return 0;
}