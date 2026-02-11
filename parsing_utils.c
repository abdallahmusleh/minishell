/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:59:52 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/11 19:16:19 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"
#include "headers/minishell.h"

void free_pipeline (t_pipeline *pipeline)
{
    int i;
    int j;
    
    if (!pipeline)
        return;
    i = 0;
    if (pipeline->commands)
    {
        while (i < pipeline->num_commands)
        {
            if (pipeline->commands[i].args)
            {
                j = 0;
                while (pipeline->commands[i].args[j])
                {
                    free(pipeline->commands[i].args[j]);
                    j++;
                }
                free(pipeline->commands[i].args);
            }
            if (pipeline->commands[i].input_fd != STDIN_FILENO)
                close(pipeline->commands[i].input_fd);
            if (pipeline->commands[i].output_fd != STDOUT_FILENO)
                close(pipeline->commands[i].output_fd);
            i++;
        }
        free(pipeline->commands);
    }
    free(pipeline);
}

int command_counter(t_token *tokens)
{
    int i;
    
    if (!tokens)
        return (0);
    i = 1;
    while (tokens && tokens->type != T_EOF)
    {
        if (tokens->type == PIPE)
            i++;
        tokens = tokens->next;
    }
    return(i);
}

void    parse_heredoc_helper(int fd[2], char *str)
{
    write(2,
		"warning: here-document delimited by end-of-file (wanted `",
		57);
    if (str)
        write(2, str, ft_strlen(str));
	write(2, "')\n", 3);
}

void    free_and_close(char *str, int fd)
{
    if (str)
        free(str);
    if (fd >= 0)
        close(fd);
}
