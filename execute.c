#include "main.h" // Include the header file
int status, pid; // Declare global variables for process status and process ID
extern int flag; // Declare an external variable flag

// Function to execute external commands
void execute_external_commands(char *input_string)
{
    int pipe_cou = 0; // Initialize pipe count
    char *argv[10], str[50]; // Declare argument array and string buffer
    strcpy(str, input_string); // Copy input string to buffer
    int ind = 0, j = 0; // Initialize indices
    char *token = strtok(str, " "); // Tokenize input string by spaces
    while (token != NULL) // Loop through tokens
    {
        argv[ind] = calloc(strlen(token) + 1, 1); // Allocate memory for argument
        strcpy(argv[ind++], token); // Copy token to argument array
        if (!strcmp(argv[ind - 1], "|")) // Check if token is a pipe
            pipe_cou++; // Increment pipe count
        token = strtok(NULL, " "); // Get next token
    }
    argv[ind] = NULL; // Null-terminate the argument array
    if (pipe_cou == 0) // If no pipes are present
    {
        switch ((pid = fork())) // Create a child process
        {
        case 0: // Child process
        {
            execvp(argv[0], argv); // Execute the command
            break; // Break out of the switch
        }
        default: // Parent process
            waitpid(pid, &status, WUNTRACED); // Wait for the child process
            // printf("\n"); // Commented out debug statement
            break; // Break out of the switch
        }
    }
    else // If pipes are present
        pipe_ex(ind, argv); // Call pipe execution function
    for (size_t i = 0; i < ind; i++) // Free allocated memory for arguments
    {
        free(argv[i]); // Free memory for each argument
    }
}

// Function to handle pipe execution
int pipe_ex(int ind, char *argv[])
{
    int back_upin = dup(0); // Backup stdin
    int back_upout = dup(1); // Backup stdout
    int com_pos[10], pipe_cou = 0, pos = 0, i = 0; // Variables for command positions, pipe count, and process IDs

    com_pos[pos] = 0; // Initialize command position array
    for (size_t i = 0; i < ind; i++) // Loop to find pipe symbols
    {
        if (!strcmp(argv[i], "|")) // Check if argument is a pipe
        {
            argv[i] = NULL; // Replace '|' with NULL for execvp
            com_pos[++pos] = i + 1; // Store position of next command
        }
    }
    int fds[2]; // File descriptors for the pipe
    for (i = 0; i < pos + 1; i++) // Loop to create processes for each command
    {
        pipe(fds); // Create a pipe
        pid = fork(); // Create a new process
        if (pid == 0) // Child process
        {
            close(fds[0]); // Close read end of the pipe
            if (i != pos) // If not the last command
                dup2(fds[1], 1); // Redirect stdout to write end of the pipe
            execvp(argv[com_pos[i]], &argv[com_pos[i]]); // Execute command
        }
        else // Parent process
        {
            close(fds[1]); // Close write end of the pipe
            dup2(fds[0], 0); // Redirect stdin to read end of the pipe
        }
    }
    close(fds[0]); // Close read end of the pipe
    close(fds[1]); // Close write end of the pipe
    dup2(back_upin, 0); // Restore stdin
    dup2(back_upout, 1); // Restore stdout
    waitpid(pid, &status, WUNTRACED); // Wait for last child process to finish
}

// Function to execute internal commands
void execute_internal_commands(char *input_string)
{
    if (!strcmp(input_string, "exit")) // Check if command is "exit"
        exit(0); // Exit the program
    else if (!strncmp(input_string, "cd", 2)) // Check if command is "cd"
    {
        char *back_path; // Variable to store the path
        char *path = strtok(input_string, " "); // Tokenize input string by spaces
        while (path != NULL) // Loop through tokens
        {
            back_path = path; // Store the last token as the path
            path = strtok(NULL, " "); // Get next token
        }
        chdir(back_path); // Change directory to the specified path
    }
    else if (!strcmp(input_string, "pwd")) // Check if command is "pwd"
        system("pwd"); // Execute the "pwd" command using system()
}