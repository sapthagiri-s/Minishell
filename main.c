#include "main.h" // Include the header file "main.h" for function declarations and macros

char prompt[25] = "minishell"; // Declare and initialize a prompt string with "minishell"

int main() // Main function entry point
{
    system("clear"); // Clear the terminal screen
    char *input_string = calloc(50, 1); // Allocate memory for a 50-byte string and initialize it to zero
    scan_input(prompt, input_string); // Call the function to scan user input with the prompt
}