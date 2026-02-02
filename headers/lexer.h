/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:29:28 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/02 23:22:19 by abmusleh         ###   ########.fr       */
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
    HEREDOC       // <<
}   t_token_type;

typedef struct s_token
{
    t_token_type type;
    char         *value;
    struct s_token *next;
}   t_token;

t_token *lexing(char *line);

#endif
