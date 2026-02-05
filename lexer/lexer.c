/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:29:09 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/05 00:19:11 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lexer.h"
#include "libft/libft.h"
#include "minishell.h"

static void end_of_file_token(t_token **list)
{
	char	*value;
	t_token	*token;

	value = NULL;
	token = token_list_new(EOF, value);
	if (!token)
	{
		free(value);
		lst_clear(token_list);
		return ;
	}
	ft_lstadd_back(&token_list, token);
}
static int	handle_operator(t_token **token_list, char *line, int *i)
{
	if (line[*i] == '<')
		return (handle_redirect_in(token_list, line, i));
	else if (line[*i] == '>')
		return (handle_redirect_out(token_list, line, i));
	else if (line[*i] == '|')
        return( handle_pipe(token_list, i));
	return (1);
}
static int	handle_word(t_token **token_list, int *i, char *line)
{
	t_token	*token;

	token = word_parser(line, i);
	if (!token)
	{
		lst_clear(token_list);
		return (0);
	}
	ft_lstadd_back(token_list, token);
	return (1);
}
t_token	*lexing(char *line)
{
	t_token	*token_list;
	int		i;

	if (!line || !*line)
		return (NULL);
	token_list = NULL;
	i = 0;
	while (line[i])
	{
		if (space_finder(line[i]))
			i++;
		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			if (!handle_operator(&token_list, line, &i))
				return (NULL);
		}
		else
		{
			if (!handle_word(&token_list, &i, line))
				return (NULL);
		}
	}
	end_of_file_token(&token_list);
	return (token_list);
}
//ask about end of file token/ error token
