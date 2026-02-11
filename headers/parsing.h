/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:34:01 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/11 19:41:22 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "lexer.h"
#include <fcntl.h>

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

// Syntax validator
int     syntax_validator(t_token *tokens);

// Main parser function
t_pipeline  *parse_pipeline(t_token *tokens);

// Utility functions
void    free_pipeline(t_pipeline *pipeline);
int     command_counter(t_token *tokens);
int     parse_redir(t_pipeline *pipeline, t_token **tmp_tokens, int i);
void    parse_heredoc_helper(int fd[2], char *delimiter);
void    free_and_close(char *str, int fd);

#endif
