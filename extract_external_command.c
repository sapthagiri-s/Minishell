#include "main.h" // Include the header file "main.h" for function declarations and macros

void extract_external_commands(char **external_commands) // Function to extract external commands from a file
{
    int fd = open("external_command.txt", O_RDONLY); // Open the file "external_command.txt" in read-only mode
    if (fd == -1) // Check if the file failed to open
    {
        perror("open"); // Print an error message if the file could not be opened
        exit(0); // Exit the program with status 0
    }
    else
    {
        int i = 0, j = 0; // Initialize indices for characters and commands
        char ch = 0; // Variable to store the current character being read
        while (read(fd, &ch, 1) > 0) // Read one character at a time from the file
        {
            if (ch != '\n') // If the character is not a newline
                external_commands[j][i++] = ch; // Add the character to the current command
            else
            {
                external_commands[j][i - 1] = '\0'; // Null-terminate the current command
                i = 0; // Reset the character index for the next command
                j++; // Move to the next command
            }
        }
        if (i > 0) // If there are remaining characters in the last command
            external_commands[j][i] = '\0'; // Null-terminate the last command
    }
}