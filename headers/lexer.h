/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:29:28 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/06 18:19:14 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include <unistd.h>
#include <stdlib.h>
 
typedef enum e_token_type
{
    WORD,
    PIPE,
    REDIR_IN,     // <
    REDIR_OUT,    // >
    REDIR_APPEND, // >>
    HEREDOC,      // <<
    T_EOF
}   t_token_type;

typedef struct s_token
{
    t_token_type type;
    char         *value;
    struct s_token *next;
}   t_token;

t_token *lexing(char *line);
t_token *token_list_new(t_token_type type, char *value);
void	ft_lstadd_back(t_token **list, t_token *new);
void	lst_clear(t_token **list);
int		space_finder(char c);
t_token	*word_parser(char *line, int *i);
int		handle_redirect_in(t_token **token_list, char *line, int *i);
int		handle_redirect_out(t_token **token_list, char *line, int *i);
int		handle_pipe(t_token **token_list, int *i);

#endif
