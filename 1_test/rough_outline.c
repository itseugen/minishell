/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:34:31 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/03 22:37:03 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

this is how parsing would go :-

1.//Tokenization:

The first step in parsing is tokenization, where we split the input string into smaller units called tokens. Tokens are typically separated by spaces, but they can also include special characters like quotes (" or ') or metacharacters (e.g., |, <, > for piping and redirection).
we need to handle tokenization in a way that respects quoted strings, so spaces within quotes are not treated as token separators.

2.//Command Structure:

After tokenization, we need to recognize the structure of the input, which typically consists of one or more commands separated by pipe symbols (|), along with input and output redirection symbols.
For example, the input ls -l | grep .txt > output.txt can be broken down into multiple commands: ls -l, grep .txt, and output.txt.

3.//Command and Argument Separation:

Once we've identified commands, we need to further separate them into the command name and its arguments.
The command name is the first token, and the subsequent tokens are arguments to that command.

4.//Redirection and Piping:

Identify and process input/output redirection and piping symbols. These symbols indicate that the standard input or output of a command should be connected to a file or another command.

5.//Quoting:

Handle quotes properly to preserve the contents as a single argument, even if they contain spaces or special characters.
Common types of quotes include double quotes (") and single quotes (').

6.//Escaping:

Recognize escape sequences to properly handle characters that have special meanings, such as backslashes (\).

7.//Variable Expansion:

Optionally, we can implement support for expanding environment variables. For example, if the user enters $HOME, it should be replaced with the actual value of the HOME environment variable.

8.//Error Handling:

Implement robust error handling for cases when the input is not well-formed, such as mismatched quotes or incorrect use of redirection and piping symbols.

9.//Data Structure:

Create data structures to store the parsed tokens and their relationships, such as command structures, arguments, and redirection specifications.

10.//Command Execution:

Once parsing is complete, we can execute the commands based on the parsed information.
