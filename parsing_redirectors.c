/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirectors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:56:46 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/15 18:35:33 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"
#include "headers/parsing.h"
#include "libft/libft.h"

static int	redir_target_ok(t_token *token)
{
	if (!token || !token->next || token->next->type != WORD)
	{
		write(2, "syntax error near unexpected token `newline'\n", 45);
		return (0);
	}
	return (1);
}

static int	parse_redir_in(t_pipeline *pipeline, t_token **token, int i)
{
    int	fd;

    if (!redir_target_ok(*token))
        return (0);
    if (pipeline->commands[i].input_fd != STDIN_FILENO)
        close(pipeline->commands[i].input_fd);
    fd = open((*token)->next->value, O_RDONLY);
    if (fd == -1)
    {
        write(2, "invalid fd", 10);
        return (0);
    }
    pipeline->commands[i].input_fd = fd;
    *token = (*token)->next;
    return (1);
}

static int	parse_redir_out(t_pipeline *pipeline, t_token **token, int i)
{
    int	fd;

    if (!redir_target_ok(*token))
        return (0);
    if (pipeline->commands[i].output_fd != STDOUT_FILENO)
        close(pipeline->commands[i].output_fd);
    fd = open((*token)->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        write(2, "invalid fd", 10);
        return (0);
    }
    pipeline->commands[i].output_fd = fd;
    *token = (*token)->next;
    return (1);
}

static int	parse_redir_append(t_pipeline *pipeline, t_token **token, int i)
{
    int	fd;

    if (!redir_target_ok(*token))
        return (0);
    if (pipeline->commands[i].output_fd != STDOUT_FILENO)
        close(pipeline->commands[i].output_fd);
    fd = open((*token)->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        write(2, "invalid fd", 10);
        return (0);
    }
    pipeline->commands[i].output_fd = fd;
    *token = (*token)->next;
    return (1);
}

int	parse_redir(t_pipeline *pipeline, t_token **tmp_tokens, int i)
{
    if ((*tmp_tokens)->type == REDIR_IN)
        return (parse_redir_in(pipeline, tmp_tokens, i));
    else if ((*tmp_tokens)->type == REDIR_OUT)
        return (parse_redir_out(pipeline, tmp_tokens, i));
    else if ((*tmp_tokens)->type == REDIR_APPEND)
        return (parse_redir_append(pipeline, tmp_tokens, i));
    else if ((*tmp_tokens)->type == HEREDOC)
        return (parse_heredoc(pipeline, tmp_tokens, i));
    return (1);
}
