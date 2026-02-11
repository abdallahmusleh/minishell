/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirectors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:56:46 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/11 16:33:43 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"
#include "headers/parsing.h"
#include "libft/libft.h"

static int  parse_redir_in(t_pipeline *pipeline, t_token **token, int i)
{
    int fd;

    if (pipeline->commands[i].input_fd != STDIN_FILENO)
        close(pipeline->commands[i].input_fd);
    fd = open((*token)->next->value, O_RDONLY);
    if (fd == -1)
    {
        write(2, "invalid fd", 11);
        return(0);    
    }
    pipeline->commands[i].input_fd = fd;
    *token = (*token)->next;
    return(1);
}

static int  parse_redir_out(t_pipeline *pipeline, t_token **token, int i)
{
    int fd;

    if (pipeline->commands[i].output_fd != STDOUT_FILENO)
        close(pipeline->commands[i].output_fd);
    fd = open((*token)->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        write(2, "invalid fd", 11);
        return(0);    
    }
    pipeline->commands[i].output_fd = fd;
    *token = (*token)->next;
    return(1);
}

static int  parse_redir_append(t_pipeline *pipeline, t_token **token, int i)
{
    int fd;

    if (pipeline->commands[i].output_fd != STDOUT_FILENO)
        close(pipeline->commands[i].output_fd);
    fd = open((*token)->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        write(2, "invalid fd", 11);
        //check actual error msg
        return(0);    
    }
    pipeline->commands[i].output_fd = fd;
    *token = (*token)->next;
    return(1);
}
void    parse_heredoc_helper(int fd[2], char *str)
{
    close(fd[0]);
    close(fd[1]);
    write(2,
		"warning: here-document delimited by end-of-file (wanted `",
		58);
	write(2, str, ft_strlen(str));
	write(2, "')\n", 3);
}
void    free_and_close(char *str, int fd)
{
    free(str);
    close(fd);
}
static int parse_heredoc(t_pipeline *pipeline, t_token **tokens, int i)
{
    int fd[2];
    char *str;
    
    if (pipe(fd) == -1)
	{
        write (2, "pipe error", 11);
        return (0);
    }
    while (1)
    {
        str = readline(">");
        if (!str)
        {
            parse_heredoc_helper(fd, str);
            return(0);
        }
        if (!ft_strcmp(str, (*tokens)->next->value))
            break;
        write(fd[1], str, ft_strlen(str));
        write(fd[1], "\n", 1);
        free(str);
    }
    free_and_close(str, fd[1]);
    *tokens = (*tokens)->next;
    return(fd[0]);
}

static int parse_redir(t_pipeline *pipeline, t_token **tmp_tokens, int i)
{
    if ((*tmp_tokens)->type == REDIR_IN)
        return(parse_redir_in(pipeline, tmp_tokens, i));
    else if ((*tmp_tokens)->type == REDIR_OUT)
        return(parse_redir_out(pipeline, tmp_tokens, i));
    else if ((*tmp_tokens)->type == REDIR_APPEND)
       return(parse_redir_append(pipeline, tmp_tokens, i));
    else if ((*tmp_tokens)->type == HEREDOC)
        return(parse_heredoc(pipeline, tmp_tokens, i));
    return(1);
}
