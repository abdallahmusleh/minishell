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
// static t_token word_parser(char *line, int *i)
// {
//     //check what to do for commands with spaces in between that arent in between quotations
//     char *word;
//     int tmp;
//     int quotation_counter;

//     tmp = *i + 1;
//     quotation_counter = 0;
//     if (line[*i] == '\'' || line[*i] == '"')//check how to see if current character is a quotation
//     {
//         while (line[tmp])
//         {
//             if (line[tmp] == line[*i])
//                 quotation_counter++;
//             tmp++;
//         }
//         if (quotation_counter == 0)
//             return(error unclosed quote);//check if this is correct return
//         tmp = *i + 1;
//         while (line[tmp] && line[tmp] != line[*i])
//             tmp++;
//         word = ft_substr(line, *i + 1, tmp - *i - 1);
//         if (!word)
//             return(NULL);
//         *i = tmp + 1;
//         return(token_list_new(WORD, word));
//     }
//     while (line[tmp] && line[tmp] != '<' && line[tmp] != '>' && line[tmp] != '|' && !space_finder(line[tmp]))
//         tmp++;
//     word = ft_substr(line, *i, tmp - *i);
//     if (!word)
//         return(NULL);
//     *i = tmp;
//     return(token_list_new(WORD, word));
// }
// static t_token word_parser(char *line, int *i)
// {
//     char *word;
//     int tmp;

//     tmp = *i //+ 1;
//     while (line[tmp])
//     {
//         if (space_finder(line[tmp]) || line[tmp] == '|' ||
//             line[tmp] == '<' || line[tmp] == '>')
//             break;
//     if (line[tmp] == '\'' || line[tmp] == '"')//check how to see if current character is a quotation
//     {
//         tmp++;
//         while (line[tmp] && line[tmp] != line[*i])
//             tmp++;
//         if (!line[tmp])
//             return(error unclosed quote);
//         // word = ft_substr(line, *i + 1, tmp - *i - 1);
//         // if (!word)
//         //     return(NULL);
//         // return(token_list_new(WORD, word));
//     }
//     else
//         tmp++;
//     word = ft_substr(line, *i, tmp - *i);
//     if (!word)
//         return(NULL);
//     *i = tmp + 1;
//     return(remove_quotes(token_list_new(WORD, word)));
//     }
// }
char *substr_and_quotes_remover(char *line, int start, int *i)
{
    char *newstr;
    char *word;
    int x;
    int j;

    x = 0;
    j = 0;
    word = ft_substr(line, start, *i - start);
    if (!word)
        return (NULL);
    newstr = malloc(ft_strlen(word) + 1);
    if (!newstr)
    {
        free(word);
        return (NULL);
    }
    while (word[x])
    {
        if (word[x] != '\'' && word[x] != '"')
            newstr[j++] = word[x];
        x++;
    }
    newstr[j] = '\0';
    free(word);
    return (newstr);
}
t_token *word_parser(char *line, int *i)
{
    int start;
    char quote;
    char *word;

    start = *i;
    while (line[*i])
    {
        if (space_finder(line[*i]) || line[*i] == '|' ||
            line[*i] == '<' || line[*i] == '>')
            break;
        if (line[*i] == '\'' || line[*i] == '"')
        {
            quote = line[*i];
            (*i)++;
            while (line[*i] && line[*i] != quote)
                (*i)++;
            if (!line[*i])
                return (NULL);
            (*i)++;
        }
        else
            (*i)++;
    }
    return (token_list_new(WORD, substr_and_quotes_remover(line, start, i)));
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
            if (line[i + 1] && line[i + 1] == '<')
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
            if (line[i + 1] && line[i + 1] == '>')
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
        {
            t_token *tok = word_parser(line, &i);
            if (tok)
                ft_lstadd_back(&token_list, tok);
            else
                lst_clear(token_list);
                return(NULL);
        }
    }
    return(token_list);
}
