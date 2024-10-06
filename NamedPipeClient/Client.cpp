#include <iostream>
#include <windows.h>

#define PIPE(name) TEXT("\\\\.\\pipe\\"##name)

typedef unsigned long int uint32;

constexpr wchar_t my_pipe_name[] = PIPE("my_pipe");

int main(void)
{
    // Creating handle for a "file", which really is a pipe
    HANDLE pipe = CreateFileW(my_pipe_name,
        GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        nullptr);

    // If pipe exists
    if (pipe != INVALID_HANDLE_VALUE)
    {
        std::cout << "Pipe initialized. You can enter some messages:\n";

        uint32 bytesWritten;
        char buffer[1024] = { '1' };

        const size_t bufferSize = sizeof(buffer);
        while (buffer[0] != '0')
        {
            // Read some input from console
            std::cin.getline(buffer, bufferSize);

            // Write input data into pipe
            WriteFile(pipe, buffer, bufferSize - 1, &bytesWritten, nullptr);
        }

        CloseHandle(pipe);
    }

    std::cout << "Client stopped." << std::endl;

    return (0);
}