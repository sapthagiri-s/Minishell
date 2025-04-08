#include "main.h" // Include the header file "main.h"
extern int flag, pid, flag1; // Declare external variables
extern char prompt[25]; // Declare an external character array for the prompt
extern Slist *head; // Declare an external pointer to the head of the linked list
extern char strrr[50]; // Declare an external character array for storing a string

// Function to handle the "echo" command
void echo(char *input_string, int status)
{
    // Check if the input is "echo $?" and print the status
    if (!strncmp(input_string, "echo $?", strlen("echo $?")))
        printf("%d\n", status);
    // Check if the input is "echo $$" and print the process ID
    else if (!strncmp(input_string, "echo $$", strlen("echo $$")))
        printf("%d\n", getpid());
    // Check if the input is "echo $SHELL" and print the shell environment variable
    else if (!strncmp(input_string, "echo $SHELL", strlen("echo $SHELL")))
        printf("%s\n", getenv("SHELL"));
    // Handle generic "echo" commands and print the input string
    else if (!strncmp(input_string, "echo", 4))
        printf("%s\n", &input_string[5]);
}

// Signal handler function
void signal_handler(int sig_num)
{
    // Handle SIGINT (Ctrl+C)
    if (sig_num == SIGINT)
    {
        if (pid != 0) // Check if a process ID exists
        {
            flag1 = !flag1; // Toggle the flag1 variable
            pid = 0; // Reset the process ID
        }
    }
    // Handle SIGTSTP (Ctrl+Z)
    else if (sig_num == SIGTSTP)
    {
        if (pid != 0) // Check if a process ID exists
        {
            insert_at_first(&head, pid, strrr); // Insert the process into the linked list
            pid = 0; // Reset the process ID
            flag1 = !flag1; // Toggle the flag1 variable
        }
    }
    else
        printf("\n"); // Print a newline for other signals

    // Print the prompt if flag1 is set
    if (flag1)
        printf(ANSI_COLOR_GREEN "\n%s$" ANSI_COLOR_RESET, prompt);
    fflush(stdout); // Flush the output buffer
}

// Function to insert a node at the beginning of the linked list
int insert_at_first(Slist **head, int pid, char *data)
{
    Slist *new = malloc(sizeof(Slist)); // Allocate memory for a new node
    if (new == NULL) // Check if memory allocation failed
        return FAILURE;
    if (*head == NULL) // Check if the list is empty
    {
        *head = new; // Set the new node as the head
        new->pid = pid; // Assign the process ID to the new node
        strcpy(new->command, data); // Copy the command to the new node
        new->link = NULL; // Set the link to NULL
    }
    else
    {
        new->pid = pid; // Assign the process ID to the new node
        strcpy(new->command, data); // Copy the command to the new node
        new->link = *head; // Link the new node to the current head
        *head = new; // Update the head to the new node
    }
    return SUCCESS; // Return success
}

// Function to print the linked list
void print_list(Slist *head)
{
    if (head != NULL) // Check if the list is not empty
    {
        Slist *temp = head; // Temporary pointer to traverse the list
        while (temp != NULL) // Traverse the list until the end
        {
            printf("[%d]    %s\n", temp->pid, temp->command); // Print the process ID and command
            temp = temp->link; // Move to the next node
        }
    }
}