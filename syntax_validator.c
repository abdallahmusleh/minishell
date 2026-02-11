/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:38:17 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/11 20:35:36 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lexer.h"
#include "headers/minishell.h"
#include "libft/libft.h"

static int pipe_validator(t_token *tokens)
{
    t_token *tmp_tokens;

    tmp_tokens = tokens;
    if (tmp_tokens->type == PIPE)
        return (0);
    while (tmp_tokens && tmp_tokens->type != T_EOF)
    {
        if (tmp_tokens->type == PIPE)
        {
            if (tmp_tokens->next && tmp_tokens->next->type == T_EOF)
                return(0);
            if (tmp_tokens->next && tmp_tokens->next->type == PIPE)
                return(2);
        }
        tmp_tokens = tmp_tokens->next;
    }
    return (1);
}

static int redirections_validator(t_token *tokens)
{
    t_token *tmp_tokens;

    tmp_tokens = tokens;
    while (tmp_tokens && tmp_tokens->type != T_EOF)
    {
        if (tmp_tokens->type == REDIR_IN || tmp_tokens->type == REDIR_OUT
            || tmp_tokens->type == REDIR_APPEND || tmp_tokens->type == HEREDOC)
        {
            if (!tmp_tokens->next || tmp_tokens->next->type != WORD)
                return(0);
            //check if i need to handle multiple conflicting redirections ex: cmd < file1 < file2
        }
        tmp_tokens = tmp_tokens->next;
    }
    return(1);
}

int syntax_validator(t_token *tokens)
{
    if (!tokens || tokens->type == T_EOF)
        return (1);
    if (!pipe_validator(tokens))
    {
        write(2, "minishell: syntax error near unexpected token `newline'\n", 57);
        return (0);
    }
    if (pipe_validator(tokens) == 2)
    {
        write(2, "syntax error near unexpected token `|'\n", 40);
        return(0);
    }
    if (!redirections_validator(tokens))
    {
        write(2, "syntax error near unexpected token `newline'\n", 46);
        return (0);
    }
    return (1);
}
