/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:29:09 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/02 23:36:57 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lexer.h"
#include "libft/libft.h"

static int space_finder(char c)
{
    if (c == 32 || (c >= 9 && c <= 13))//check what counts as empty space
        return (1);
    else
        return (0);
}
static t_token word_parser(char *line, int *i)
{
    //check what to do for commands with spaces in between that arent in between quotations
    char *word;
    int tmp;
    int quotation_counter;

    tmp = i + 1;
    quotation_counter = 0;
    if (line[i] == '' || line[i] == "")//check how to see if current character is a quotation
    {
        while (line[tmp])
        {
            if (line[tmp] == line[i])
                quotation_counter++;
            tmp++;
        }
        if (quotation_counter = 0)
            return(free and error or 0 check later);
        while (line[tmp] != line[i])
            tmp++;
        word = ft_substr(line, i, tmp - i);
        if (!word)
            return(NULL);
        i = tmp;
        return(token_list_new(WORD, word));
    }
    while (line[i] && line[i] != '<' && line[i] != '>' && line[i] != '|' && !space_finder(line[i]))
        tmp++;
    word = ft_substr(line, i, tmp - i);
    if (!word)
        return(NULL);
    i = tmp;
    return(token_list_new(WORD, word));
}
t_token *lexing(char *line)
{
    t_token *token_list;
    int i;

    token_list = NULL;
    i = 0;
    while (line[i])
    {
        if (space_finder(line[i]))
            i++;
        else if (line[i] == '<')
        {
            if (line[i + 1] == '<')
            {
                ft_lstadd_back(&token_list, token_list_new(HEREDOC, "<<"));
                i = i + 2;
            }
            else
            {
                ft_lstadd_back(&token_list, token_list_new(REDIR_IN, "<"));
                i++;
            }
        }
        else if (line[i] == '>')
        {
            if (line[i + 1] == '>')
            {
                ft_lstadd_back(&token_list, token_list_new(REDIR_APPEND, ">>"));
                i = i + 2;
            }
            else
            {
                ft_lstadd_back(&token_list, token_list_new(REDIR_OUT, ">"));
                i++;
            }
        }
        else if (line[i] == '|')
        {
            ft_lstadd_back(&token_list, token_list_new(PIPE, "|"));
            i++;
        }
        else
            ft_lstadd_back(&token_list, word_parser(line, &i));
    }
    return(token_list);
}
// node = ft_lstnew(value);
// 		if (!node)
// 		{
// 			lst_clear(list_a);
// 			return (0);
// 		}
// 		ft_lstadd_back(list_a, node);
