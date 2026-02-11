/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:01:27 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/06 18:20:48 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "headers/lexer.h"
#include "libft/libft.h"

int	space_finder(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
static void quotes_remover(int *x, int *j, char *word, char *newstr)
{
    if (word[*x] == '\'' || word[*x] == '"')
		{
            char quote = word[*x];
            (*x)++; 
            while (word[*x] && word[*x] != quote)
				newstr[(*j)++] = word[(*x)++];
            if (word[*x] == quote)
                (*x)++; 
        }
        else
			newstr[(*j)++] = word[(*x)++];
}
static char	*substr_and_quotes_remover(char *line, int start, int *i)
{
	char	*newstr;
	char	*word;
	int		x;
	int		j;

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
       quotes_remover(&x, &j, word, newstr);
	newstr[j] = '\0';
	free(word);
	return (newstr);
}
static int	find_end_of_word(char *line, int *i)
{
    char	quote;

    while (line[*i])
    {
        if (space_finder(line[*i]) || line[*i] == '|' ||
            line[*i] == '<' || line[*i] == '>')
            return (1);
        if (line[*i] == '\'' || line[*i] == '"')
        {
            quote = line[*i];
            (*i)++;
            while (line[*i] && line[*i] != quote)
                (*i)++;
            if (!line[*i])
            {
                write(2, "syntax error: unclosed quote\n", 29);
                return (0);
            }
            (*i)++;
        }
        else
            (*i)++;
    }
    return (1);
}
t_token *word_parser(char *line, int *i)
{
    int start;
    char *word;
    t_token *token;
    
    start = *i;
    if (!find_end_of_word(line, i))
        return(NULL);
    word = substr_and_quotes_remover(line, start, i);
    if (!word)
        return (NULL);
    // if (!*word)//check if we send empty word instead of NULL
    // {
    //     free(word);
    //     return (NULL);
    // }
    token = token_list_new(WORD, word);
    if (!token)
    {
        free(word);
        return (NULL);
    }
    return (token);
}
