/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 23:58:27 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/04 23:59:37 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "headers/lexer.h"
#include "libft/libft.h"

static int	handle_heredoc(t_token **token_list, int *i)
{
	char	*value;
	t_token	*token;

	value = ft_strdup("<<");
	if (!value)
	{
		lst_clear(token_list);
		return (0);
	}
	token = token_list_new(HEREDOC, value);
	if (!token)
	{
		free(value);
		lst_clear(token_list);
		return (0);
	}
	ft_lstadd_back(token_list, token);
	*i = *i + 2;
	return (1);
}
static int	handle_append(t_token **token_list, int *i)
{
	char	*value;
	t_token	*token;

	value = ft_strdup(">>");
	if (!value)
	{
		lst_clear(token_list);
		return (0);
	}
	token = token_list_new(REDIR_APPEND, value);
	if (!token)
	{
		free(value);
		lst_clear(token_list);
		return (0);
	}
	ft_lstadd_back(token_list, token);
	*i = *i + 2;
	return (1);
}
int	handle_redirect_in(t_token **token_list, char *line, int *i)
{
	char	*value;
	t_token	*token;

	if (line[*i + 1] && line[*i + 1] == '<')
		return (handle_heredoc(token_list, i));
	value = ft_strdup("<");
	if (!value)
	{
		lst_clear(token_list);
		return (0);
	}
	token = token_list_new(REDIR_IN, value);
	if (!token)
	{
		free(value);
		lst_clear(token_list);
		return (0);
	}
	ft_lstadd_back(token_list, token);
	(*i)++;
	return (1);
}
int	handle_redirect_out(t_token **token_list, char *line, int *i)
{
	char	*value;
	t_token	*token;

	if (line[*i + 1] && line[*i + 1] == '>')
		return (handle_append(token_list, i));
	value = ft_strdup(">");
	if (!value)
	{
		lst_clear(token_list);
		return (0);
	}
	token = token_list_new(REDIR_OUT, value);
	if (!token)
	{
		free(value);
		lst_clear(token_list);
		return (0);
	}
	ft_lstadd_back(token_list, token);
	(*i)++;
	return (1);
}
int handle_pipe(t_token **token_list, int *i)
{
    char	*value;
    t_token	*token;

    value = ft_strdup("|");
    if (!value)
    {
        lst_clear(token_list);
        return (0);
    }
    token = token_list_new(PIPE, value);
    if (!token)
    {
        free(value);
        lst_clear(token_list);
        return (0);
    }
    ft_lstadd_back(token_list, token);
    (*i)++;
    return (1);
}