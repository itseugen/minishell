/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:27:24 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/16 14:16:56 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Enumeration for different types of nodes in the AST
typedef enum e_node_kind
{
	N_CMD, //command node
	N_PIPE, // pipe node
	N_AND, // logical AND node (&&)
	N_OR, // logical OR node (||)
} t_node_kind;

// Enumeration for different types of I/O operations
typedef enum e_io_kind
{
	IO_IN, // Input redirection (<)
	IO_OUT, // Output redirection (>)
	IO_APPEND, // Output redirection append(>>)
	IO_HEREDOC, // Here Document (<<)
} t_io_kind;

// Structure for I/O node in the AST
typedef struct s_node_io
{
	t_io_kind			kind; // Kind of I/O operation
	char				*value; // File or here document value
	struct s_node_io	*next; // pointer to the next I/O node
}	t_node_io;

// Structure for a node in the AST
typedef struct s_node
{
	t_node_kind			kind; // Kind of node (eg. cmd, pipe, AND, OR)
	char				*args; // Args for the command node
	t_node_io			*io_list; //List of I/O nodes associated with the command node
	struct s_node	*left; // Left child of the node (for binary operations)
	struct s_node	*right; // Right child of the node (for binary operations)
}	t_node;
