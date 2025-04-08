#include "main.h" // Include the header file "main.h"
extern int status; // Declare an external variable 'status'
int flag, flag1 = 1; // Declare flags for control flow
char *external_command[200]; // Array to store external commands
Slist *head = NULL; // Pointer to the head of a linked list
char strrr[50]; // Buffer to store a string

// Function to scan user input and process commands
void scan_input(char *prompt, char *input_string)
{
    signal(SIGINT, signal_handler); // Set up signal handler for SIGINT
    signal(SIGTSTP, signal_handler); // Set up signal handler for SIGTSTP

    for (int i = 0; i < 200; i++) // Loop to allocate memory for commands
        external_command[i] = malloc(100); // Allocate memory for each command
    extract_external_commands(external_command); // Extract external commands

    while (1) // Infinite loop to continuously process input
    {
        char str[50] = {0}; // Buffer to store a temporary string
        flag = 0; // Reset flag
        flag1 = 1; // Reset flag1
        fflush(stdout); // Flush the output buffer

        if (flag1) // Check if flag1 is set
        {
            printf(ANSI_COLOR_GREEN "%s$" ANSI_COLOR_RESET, prompt); // Print the prompt
        }

        scanf("%[^\n]", input_string); // Read input until a newline
        getchar(); // Consume the newline character
        strcpy(str, input_string); // Copy input to a temporary string
        strcpy(strrr, input_string); // Copy input to a global buffer
        fflush(stdout); // Flush the output buffer

        if (input_string[0] != '\n') // Check if input is not just a newline
        {
            if (!strncmp("PS1", input_string, 3)) // Check if input starts with "PS1"
                copy_change(prompt, input_string); // Change the prompt
            else
            {
                if (strlen(input_string) > 0) // Check if input is not empty
                {
                    char *ptr = get_command(str); // Get the command from input
                    int ret = check_command_type(ptr); // Check the type of command

                    switch (ret) // Handle different command types
                    {
                    case 1: // Internal command
                    {
                        execute_internal_commands(input_string); // Execute internal command
                        break;
                    }
                    case 2: // External command
                    {
                        execute_external_commands(input_string); // Execute external command
                        break;
                    }
                    case 3: // Job control commands
                    {
                        if (!strncmp(input_string, "jobs", 4)) // Check if command is "jobs"
                        {
                            print_list(head); // Print the list of jobs
                        }
                        else if (!strncmp(input_string, "fg", 2)) // Check if command is "fg"
                        {
                            if (head == NULL) // Check if job list is empty
                                printf("no jobs\n"); // Print no jobs message
                            else
                            {
                                int pid = head->pid; // Get the process ID of the job
                                strcpy(input_string, head->command); // Copy the command
                                head = head->link; // Move to the next job
                                kill(pid, SIGCONT); // Continue the process
                                waitpid(pid, &status, WUNTRACED); // Wait for the process
                            }
                        }
                        else if (!strncmp(input_string, "bg", 2)) // Check if command is "bg"
                        {
                            if (head == NULL) // Check if job list is empty
                                printf("no jobs\n"); // Print no jobs message
                            else
                            {
                                int pid = head->pid; // Get the process ID of the job
                                strcpy(input_string, head->command); // Copy the command
                                head = head->link; // Move to the next job
                                printf("[%d] %s &\n", pid, input_string); // Print job info
                                kill(pid, SIGCONT); // Continue the process in the background
                            }
                        }
                        else
                            printf("not a command\n"); // Print invalid command message
                        break;
                    }
                    }
                }
            }
        }

        echo(input_string, status); // Echo the input and status
        for (size_t i = 0; i < 50; i++) // Clear the input string buffer
        {
            input_string[i] = '\0'; // Set each character to null
        }
    }
}

// Function to change the prompt
void copy_change(char *prompt, char *input_string)
{
    if (input_string[3] == '=' && input_string[4] != ' ') // Check for valid format
    {
        strcpy(prompt, &input_string[4]); // Copy the new prompt
    }
    else
        printf("PS1 : command not found\n"); // Print error message
}