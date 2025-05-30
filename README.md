# Minishell

**Minishell** is a simple shell implementation in C that supports core shell functionalities such as executing built-in and external commands, handling pipes, managing jobs, and processing signals.

---

## Features

- ✅ **Built-in Commands**: Supports `echo`, `cd`, `pwd`, `exit`, and more.
- ✅ **External Commands**: Executes external programs using `execvp`.
- ✅ **Piping**: Handles command chaining using pipes (e.g., `ls | grep file`).
- ✅ **Job Control**: Manage background jobs with `jobs`, `fg`, and `bg`.
- ✅ **Signal Handling**: Properly responds to signals like `SIGINT` (Ctrl+C) and `SIGTSTP` (Ctrl+Z).
- ✅ **Custom Prompt**: Customize the shell prompt using the `PS1` variable.

---

## File Structure

### Source Files

| File Name                    | Description                                                                 |
|-----------------------------|-----------------------------------------------------------------------------|
| `main.c`                    | Entry point of the shell; initializes and manages the shell loop.           |
| `scan_input.c`              | Reads and parses user input; manages job control.                           |
| `execute.c`                 | Handles execution of built-in/external commands and piping.                 |
| `echo.c`                    | Implements the `echo` command and signal handling.                          |
| `extract_external_command.c`| Loads and verifies supported external commands from a file.                 |
| `get_command.c`             | Identifies and categorizes commands.                                        |

### Header File

- `main.h`: Contains global definitions, macros, and function prototypes.

### Data File

- `external_command.txt`: Contains a list of allowed external commands for security and execution validation.

---

## How to Build and Run

1. **Compile the Shell**:

   ```bash
   gcc -o minishell main.c scan_input.c execute.c echo.c extract_external_command.c get_command.c
   ```

2. **Run the Shell**:

   ```bash
   ./minishell
   ```

---

## Usage

### Built-in Commands

- `echo Hello World` → Prints "Hello World".
- `pwd` → Displays the current working directory.
- `cd <directory>` → Changes the current directory.
- `exit` → Exits the shell.

### Piping

- Example:  
  ```bash
  ls | grep file
  ```  
  Lists files that contain "file" in their names.

### Job Control

- `jobs` → Lists background jobs.
- `fg` → Brings the most recent background job to the foreground.
- `bg` → Resumes the most recent background job in the background.

### Custom Prompt

- Change the shell prompt:
  ```bash
  PS1=YourPrompt>
  ```

### Signal Handling

- `Ctrl+C` (SIGINT): Interrupts the currently running foreground process.
- `Ctrl+Z` (SIGTSTP): Suspends the current process and places it in the background job list.

---

## Code Highlights

- 🧠 **Linked List Job Management**: Uses a linked list to manage and track background processes.
- 📦 **Dynamic Memory Allocation**: Dynamically allocates memory for command inputs and arguments.
- 🎨 **Colorful Prompt**: Shell prompt is styled using ANSI green color codes.

---

## Limitations

- No support for I/O redirection (`>`, `<`, `>>`).
- Fixed buffer sizes for command inputs.
- Only executes external commands listed in `external_command.txt`.

---

## Future Improvements

- ➕ Add support for input/output redirection.
- 📈 Improve memory handling for large/complex inputs.
- 🚨 Enhance error handling and debugging utilities.

---

## License

This project is open-source and distributed under the [MIT License](https://opensource.org/licenses/MIT).
