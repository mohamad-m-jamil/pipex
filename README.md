# Pipex

## Overview

The `pipex` project is a C program that simulates a simple pipe between two commands. It uses UNIX system calls to create a pipeline between two processes. The program reads input from a file, executes the first command with this input, and then pipes the output of this command to the second command, which writes the result to an output file.

## Requirements

- **Unix-based Operating System** (Linux, macOS, etc.)
- **C Compiler** (gcc or clang)
- **Make Utility** for building the project

## Features

- Read input from a specified file.
- Execute the first command with input from the file.
- Pipe the output of the first command to the second command.
- Write the output of the second command to a specified file.
- Error handling for file operations and process execution.

## Usage

```bash
./pipex infile cmd1 cmd2 outfile
```

- `infile`: The input file to read data from.
- `cmd1`: The first command to execute.
- `cmd2`: The second command to execute.
- `outfile`: The file to write the output of the second command.

## Compilation

1. **Clone the repository** (if applicable):
   ```bash
   git clone https://github.com/mohamad-m-jamil/pipex
   ```

2. **Navigate to the project directory**:
   ```bash
   cd pipex
   ```

3. **Build the project** using `make`:
   ```bash
   make
   ```

4. **Run the executable**:
   ```bash
   ./pipex infile "cmd1" "cmd2" outfile
   ```

## Example

Given an input file `input.txt` containing:
```
hello world
```

Run the following command to convert all text to uppercase and write it to `output.txt`:
```bash
./pipex input.txt "tr '[:lower:]' '[:upper:]'" "sed 's/ /_/g'" output.txt
```

This command sequence will:
1. Read from `input.txt`.
2. Convert all lowercase characters to uppercase.
3. Replace spaces with underscores.
4. Write the result to `output.txt`.

## File Structure

- `pipex.c`: Contains the main program logic.
- `pipex_utils.c`: Contains utility functions used by `pipex.c`.
- `pipex.h`: Header file containing function prototypes and constants.

## Functions

### `check_files`

Checks if the input and output files can be opened. It returns 1 on success and 0 on failure.

### `first_execute`

Sets up the environment to execute the first command, redirects input/output as needed, and executes the command.

### `second_execute`

Sets up the environment to execute the second command, redirects input/output as needed, and executes the command.

### `main`

Main function that parses command-line arguments, handles file operations, creates a pipe, forks processes, and manages execution of commands.

## Error Handling

The program handles the following errors:
- Failure to open input or output files.
- Failure to create or use the pipe.
- Failure to fork processes.
- Failure to execute commands.

## Cleaning Up

To remove all object files and the executable, run:
```bash
make fclean
```

To clean up object files only, run:
```bash
make clean
```

To rebuild the project, run:
```bash
make re
```
