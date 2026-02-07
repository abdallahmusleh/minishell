/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:33:08 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/06 23:25:30 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"
#include "headers/minishell.h"
#include "libft/libft.h"

//work on error cleanup
//check if i will keep this
// if (tmp_tokens->type == REDIR_IN || tmp_tokens->type == REDIR_OUT 
//         || tmp_tokens->type == REDIR_APPEND || tmp_tokens->type == HEREDOC)
//         tmp_tokens = tmp_tokens->next;
static int command_counter(t_token *tokens)
{
    int i;
    
    if (!tokens)
        return (0);
    i = 1;
    while (tokens && tokens->type != T_EOF)
    {
        if (tokens->type == PIPE)
            i++;
        tokens = tokens->next;
    }
    return(i);
}

static t_pipeline *initialize_pipeline(int num_commands)
{
    t_pipeline *pipeline;
    int i;
    
    pipeline = malloc(sizeof(t_pipeline));
    if (!pipeline)
        return (NULL);
    pipeline->num_commands = num_commands;
    pipeline->commands = malloc(sizeof(t_command) * num_commands);
    if (!pipeline->commands)
    {
        free(pipeline);
        return (NULL);
    }
    i = 0;
    while (i < num_commands)
    {
        pipeline->commands[i].args = NULL;
        pipeline->commands[i].input_fd = STDIN_FILENO;
        pipeline->commands[i].output_fd = STDOUT_FILENO;
        i++;
    }
    return (pipeline);
}
void parse_redir(t_pipeline *pipeline, t_token *tmp_tokens, int i)
{
    if (tmp_tokens->type == REDIR_IN)
        parse_redir_in();
    if (tmp_tokens->type == REDIR_OUT)
        parse_redir_out();
    if (tmp_tokens->type == REDIR_APPEND)
        parse_redir_append();
    if (tmp_tokens->type == HEREDOC)
        parse_heredoc();
}
static void fill_command(t_pipeline **pipeline, t_token *tokens, int count_words, int i)
{
    int j;
    t_token *tmp_tokens;

    j = 0;
    tmp_tokens = tokens;
    (*pipeline)->commands[i].args = malloc(sizeof(char *) * (count_words + 1));
    if (!(*pipeline)->commands[i].args)
            return ;
    while (j < count_words && tmp_tokens && tmp_tokens->type != T_EOF && tmp_tokens->type != PIPE)
    {
        if (tmp_tokens->type == REDIR_IN || tmp_tokens->type == REDIR_OUT 
                || tmp_tokens->type == REDIR_APPEND || tmp_tokens->type == HEREDOC)
            parse_redir(pipeline, tmp_tokens, i);
        else if (tmp_tokens->type == WORD)
        {
            (*pipeline)->commands[i].args[j] = ft_strdup(tmp_tokens->value);
            if (!(*pipeline)->commands[i].args[j])
                return;
            j++;
        }
        tmp_tokens = tmp_tokens->next;
    }
    (*pipeline)->commands[i].args[j] = NULL;
}

static void fill_command_helper(t_pipeline **pipeline, t_token *tokens)
{
    int count_words;
    t_token *tmp_tokens;
    t_token *cmd_start;
    int i;

    i = 0;
    tmp_tokens = tokens;
    while (tmp_tokens && tmp_tokens->type != T_EOF)
    {
        cmd_start = tmp_tokens;
        count_words = 0;
        while (tmp_tokens && tmp_tokens->type != PIPE && tmp_tokens->type != T_EOF)
        {
            if (tmp_tokens->type == REDIR_IN || tmp_tokens->type == REDIR_OUT 
                || tmp_tokens->type == REDIR_APPEND || tmp_tokens->type == HEREDOC)
                tmp_tokens = tmp_tokens->next;
            else if (tmp_tokens->type == WORD)
                count_words++;
            tmp_tokens = tmp_tokens->next;
        }
        fill_command(pipeline, cmd_start, count_words, i);
        i++;
        if (tmp_tokens && tmp_tokens->type == PIPE)//is this necessary or can we just go to next
            tmp_tokens = tmp_tokens->next;
    }
}
t_pipeline  *parse(t_token *tokens)
{
    t_pipeline  *pipeline;
    int num_commands;

    if (!syntax_validator(tokens))
    {
        write(2, "error: invalid syntax", 22);//could write in syntax validator file
        return (NULL);
    }
    num_commands = command_counter(tokens);
    pipeline = initialize_pipeline(num_commands);
    if (!pipeline)
        return (NULL);
    fill_command_helper(&pipeline, tokens);
    return (pipeline);
}
