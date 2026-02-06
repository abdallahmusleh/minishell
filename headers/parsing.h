/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:34:01 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/06 18:36:54 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "headers/lexer.h"
#include "fcntl.h"

typedef struct s_command
{
    char    **args;
    int     input_fd;
    int     output_fd; 
}   t_command;

typedef struct s_pipeline
{
    t_command   *commands;      // array of commands
    int         num_commands;   // how many commands (= pipes + 1)
}   t_pipeline;

// Main parser function
t_pipeline  *parse(t_token *tokens);

#endif