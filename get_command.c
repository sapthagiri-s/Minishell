#include "main.h" // Include the header file "main.h"
extern char *external_command[200]; // Declare an external array to store external commands
char *builtin[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval", "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source", "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", NULL}; // Array of built-in commands

// Function to extract the first command from the input string
char *get_command(char *input_string)
{
    int i = 0; // Initialize index to 0

    // Find the first space or end of string
    while (input_string[i] != ' ' && input_string[i] != '\0')
        i++;
    
    // Allocate memory for the command (+1 for null terminator)
    char *command = (char *)malloc(i + 1);
    if (!command) // Check if memory allocation failed
    {
        return NULL; // Return NULL if memory allocation failed
    }

    // Copy the first word into the new string
    strncpy(command, input_string, i); // Copy the first 'i' characters
    command[i] = '\0'; // Null-terminate the string
    return command; // Return the extracted command
}

// Function to check the type of command (builtin, external, or no command)
int check_command_type(char *command)
{
    int count = sizeof(builtin) / sizeof(builtin[0]); // Calculate the number of built-in commands
    for (size_t i = 0; i < count - 1; i++) // Iterate through the built-in commands
    {
        if (!strcmp(command, builtin[i])) // Check if the command matches a built-in command
            return BUILTIN; // Return BUILTIN if a match is found
    }
    for (size_t i = 0; i < 200; i++) // Iterate through the external commands
    {
        if (!strcmp(command, external_command[i])) // Check if the command matches an external command
            return EXTERNAL; // Return EXTERNAL if a match is found
    }
    return NO_COMMAND; // Return NO_COMMAND if no match is found
}
