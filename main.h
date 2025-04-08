#ifndef MAIN_H // Include guard to prevent multiple inclusions of this header file
#define MAIN_H

#include <stdio.h> // Standard I/O library
#include <string.h> // String manipulation functions
#include <stdlib.h> // Standard library for memory allocation, etc.
#include <stdio_ext.h> // Extensions for standard I/O
#include <sys/types.h> // Data types used in system calls
#include <sys/stat.h> // File status and mode information
#include <fcntl.h> // File control options
#include <unistd.h> // POSIX API for system calls
#include <signal.h> // Signal handling
#include <sys/wait.h> // Wait for process termination

#define SUCCESS 0 // Macro for success return value
#define FAILURE -1 // Macro for failure return value

// Structure definition for a linked list node
typedef struct node
{
        int pid; // Process ID
        char command[25]; // Command string
        struct node *link; // Pointer to the next node
} Slist;

#define BUILTIN 1 // Macro for built-in command type
#define EXTERNAL 2 // Macro for external command type
#define NO_COMMAND 3 // Macro for no command type

// ANSI color codes for terminal text formatting
#define ANSI_COLOR_RED "\x1b[31m" // Red color
#define ANSI_COLOR_GREEN "\x1b[32m" // Green color
#define ANSI_COLOR_YELLOW "\x1b[33m" // Yellow color
#define ANSI_COLOR_BLUE "\x1b[34m" // Blue color
#define ANSI_COLOR_MAGENTA "\x1b[35m" // Magenta color
#define ANSI_COLOR_CYAN "\x1b[36m" // Cyan color
#define ANSI_COLOR_RESET "\x1b[0m" // Reset color

// Function prototypes
void scan_input(char *prompt, char *input_string); // Scan user input
void copy_change(char *prompt, char *input_string); // Modify and copy input
char *get_command(char *input_string); // Extract command from input
int check_command_type(char *command); // Check type of command
void echo(char *input_string, int status); // Echo command implementation
void execute_internal_commands(char *input_string); // Execute built-in commands
void signal_handler(int sig_num); // Handle signals
void extract_external_commands(char **external_commands); // Extract external commands
void execute_external_commands(char *input_string); // Execute external commands
int pipe_ex(int ind, char *argv[]); // Handle piping
int insert_at_first(Slist **head, int pid, char *data); // Insert node at the beginning of the list
void print_list(Slist *head); // Print the linked list

#endif // End of include guard