/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:59:52 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/15 19:34:47 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"
#include "headers/minishell.h"

static void	free_args(char **args)
{
	int	j;

	if (!args)
		return ;
	j = 0;
	while (args[j])
	{
		free(args[j]);
		j++;
	}
	free(args);
}

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	if (!pipeline)
		return ;
	i = 0;
	while (pipeline->commands && i < pipeline->num_commands)
	{
		free_args(pipeline->commands[i].args);
		if (pipeline->commands[i].input_fd != STDIN_FILENO)
			close(pipeline->commands[i].input_fd);
		if (pipeline->commands[i].output_fd != STDOUT_FILENO)
			close(pipeline->commands[i].output_fd);
		i++;
	}
	free(pipeline->commands);
	free(pipeline);
}

int	command_counter(t_token *tokens)
{
	int	i;

	if (!tokens)
		return (0);
	i = 1;
	while (tokens && tokens->type != T_EOF)
	{
		if (tokens->type == PIPE)
			i++;
		tokens = tokens->next;
	}
	return (i);
}

void    free_and_close(char *str, int fd)
{
    if (str)
        free(str);
    if (fd >= 0)
        close(fd);
}
