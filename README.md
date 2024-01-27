<h1 align="center">
	<p>
		minishell
	</p>
</h1>
<h2 align="center">
	<p>
			As beautiful as shell
	</p>
</h2>
<p align="center">
Coded in
	<a href="https://skillicons.dev">
		<img src="https://skillicons.dev/icons?i=c" />
	</a>
</p>

---
## The project:
- Creating a simple shell.
- The first 42 team project.
---
## The program:
- Displays a promt waiting for input.
- Has a history of the last commands (since shell launch).
- Launches executables based on the PATH variable, an absolute path and a relative path.
- Handles single and double quotes.
- Implements the <,>,>> redirections.
- Has a here_doc (<<).
- Handles pipes (|).
- Has fully functional environment variables, an expander and a working $?.
- Accepts ctrl-C, ctrl-D.
### The builtins:
- **echo** with no options and the option -n.
- **cd** with a relative or absolute path and $HOME to change the current directory.
- **pwd** with no options to show the current working directory.
- **export** with no options to add variables to the environment list.
- **unset** with no options to delete variables from the environment variables.
- **env** without arguments or options to print the environment variables.
- **exit** without options to exit the shell with an exit code.
### Limitations:
- This is not a fully featured shell, it only implements key features to understand the working of a shell.
- While we used bash as a reference for functionality, this shell is not meant to replicate bash, especially for undefined behaviour.
---
## Installation and Usage
1. Clone the repository:
```shell
git clone https://github.com/itseugen/minishell
```
2. Enter the directory and build the program:
```shell
cd minishell
make
```
3. Execute the progam:
```shell
./minishell
```
---
<sub><sup>This project is part of my studies at 42 Heilbronn</sup></sub>