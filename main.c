/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:41:48 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/02 23:28:30 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "headers/lexer.h"

void parse (char *line)
{
    t_token *tokens;
    tokens = lexing(line); //code this in lexer
    if (!tokens)
        return (/*error*/);
    //validate syntax
}
int main()
{
    char *line;
    while (1)
    {
        line = readline("minishell$ ");
        if (!line)
            exit_shell();//we code this (Decide what happens on Ctrl-D, Clean up memory ,Print exit (bash does this) ,Exit with correct status)
        add_history(line);//ready function learn what this does
        parse(line); //Tokenize input, Handle quotes, Validate syntax, Expand variables, Build command structures
    }
}
