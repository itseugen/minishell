1. //mainpars Function:

Purpose: This is the main parser function that iterates through the token list and calls specific functions based on the type of operation in each token.
Functionality:
For CMD tokens, it calls the cmd_maker function.
For REDIRECT tokens, it calls the red_maker function.

Returns: Returns 0 if the parsing is successful, -1 if there is an error.

2. //cmd_maker Function:

Purpose: Creates a command structure (t_command) and populates it with information from the CMD token.
Functionality:
Allocates memory for the t_command structure.
Splits the command string into an array of strings.
Duplicates the first string (the command name) and stores it in the cmd_name field.
Sets default values for input and output file descriptors.
Attaches the t_command structure to the token.

Returns: Returns 0 if successful, -1 if there is a memory allocation error.

3. //red_maker Function:

Purpose: Handles redirection tokens and sets up the input and output file descriptors for a command.
Functionality:
Iterates backward through the tokens to find the CMD token associated with the redirection.
If it's an input redirection (<), calls in_out to extract and set the input file.
If it's an output redirection (>), calls in_out to extract and set the output file.
Opens the input or output file using ft_open.

Returns: Returns 0 if successful, -1 if there is an error opening the file.

4. //in_out Function:

Purpose: Extracts the input or output file name from the redirection token.
Functionality:
Takes a string containing the redirection token.
Allocates memory for the input or output file name.
Copies the file name from the token to the allocated memory.
Sets the input or output file name in the associated t_command structure.

Returns: Returns 0 if successful, -1 if there is a memory allocation error.

5. //ft_open Function:

Purpose: Opens a file with specific flags based on the provided parameters.
Functionality:
Takes a file name (str) and a flag (0 for input, 1 for output).
Checks if the file exists and is readable for input files.
Opens the file with appropriate flags for output files.
Returns the file descriptor if successful, -1 if there is an error.

Returns: Returns the file descriptor if successful, -1 if there is an error opening the file.

Execution_command_table functions :-

1. //cmd_counter Function:
Purpose:
Counts the number of commands in a given token list.
Assumes that pipes (|) are used as command separators.
Functionality:
Initializes n_cmds to 1 (at least one command is present).
Iterates through the token list.
If a pipe token is encountered (|), increments n_cmds.

Returns the total count of commands.

2. //commands_for_exec Function:
Purpose:
Allocates an array of t_exec* pointers to represent individual commands for execution.
Functionality:
Calls cmd_counter to determine the number of commands (n_cmds).
Allocates memory for an array of t_exec* pointers using malloc.
Iterates through the token list:
If the token represents a command, allocates memory for a t_exec structure.
Calls the fill function to populate the t_exec structure.
Increments the index i.
Adds a NULL pointer at the end of the array to indicate the end.

Returns the array of t_exec* pointers.

3. //fill Function:
Purpose:
Populates a t_exec structure with information from a t_token structure.
Functionality:
Takes a t_exec structure and a t_token structure as parameters.
Assigns the cmds, in_fd, and out_fd fields in the t_exec structure using information from the t_token structure.