/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 04:13:05 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/07 04:13:06 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function prototypes
t_token *tokenizer(char *input);
void free_tokens(t_token *token_list);
void parse(char *input, char **envp);

t_token *tokenizer(char *input)
{
    t_token *token_list = NULL;
    t_token *current = NULL;

    // tokenization logic goes here
    // This is a simplified version
    char **split = ft_split_minishell(input, ' ');
    if (split == NULL)
    {
        // Handle error
        return NULL;
    }

    int i = 0;
    while (split[i] != NULL)
    {
        t_token *token = malloc(sizeof(t_token));
        token->cmd = ft_strdup(split[i]);
        token->operation = 0; // need to assign appropriate types
        token->next = NULL;

        if (token_list == NULL)
        {
            token_list = token;
            current = token;
        }
        else
        {
            current->next = token;
            current = token;
        }

        ++i;
    }

    // Free the split array
    free_strings((void **)split);

    return token_list;
}

void free_tokens(t_token *token_list)
{
    while (token_list != NULL)
    {
        t_token *temp = token_list;
        token_list = token_list->next;
        free(temp->cmd);
        free(temp);
    }
}

void parse(char *input, char **envp)
{
    t_token *tokens = tokenizer(input);

    // Your parsing logic goes here
    while (tokens != NULL)
    {
        // Handle different token types and execute commands accordingly
        // For simplicity, just printing the content here
        printf("Command: %s\n", tokens->cmd);
        printf("ID: %d\n", tokens->operation);

        tokens->cmd = expander(tokens->cmd, envp);
        printf("Command after expand: %s\n", tokens->cmd);

        // Execute commands based on token types

        tokens = tokens->next;
    }

    // Free tokens after parsing
    free_tokens(tokens);
}

// Main function
int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    char *prompt;
    char *input;

    while (1)
    {
        prompt = get_prompt();
        input = readline(prompt);

        if (input != NULL && input[0] != '\0')
        {
            add_history(input);

            if (ft_strncmp(input, "exit", 5) == 0)
            {
                free(prompt);
                free(input);
                break;
            }

            parse(input, envp);
        }

        free(prompt);
        free(input);
    }
    return (0);
}

// need to write free_strings & add_history function.
