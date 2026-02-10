/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:33:08 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/09 20:57:12 by abmusleh         ###   ########.fr       */
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
void free_pipeline (t_pipeline *pipeline)
{
    int i;
    int j;
    
    if (!pipeline)
        return;
    i = 0;
    if (pipeline->commands)
    {
        while (i < pipeline->num_commands)
        {
            if (pipeline->commands[i].args)
            {
                j = 0;
                while (pipeline->commands[i].args[j])
                {
                    free(pipeline->commands[i].args[j]);
                    j++;
                }
                free(pipeline->commands[i].args);
            }
            if (pipeline->commands[i].input_fd != STDIN_FILENO)
                close(pipeline->commands[i].input_fd);
            if (pipeline->commands[i].output_fd != STDOUT_FILENO)
                close(pipeline->commands[i].output_fd);
            i++;
        }
        free(pipeline->commands);
    }
    free(pipeline);
}

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

static int  parse_redir_in(t_pipeline *pipeline, t_token **token, int i)
{
    int fd;

    if (pipeline->commands[i].input_fd != STDIN_FILENO)
        close(pipeline->commands[i].input_fd);
    fd = open((*token)->next->value, O_RDONLY);
    if (fd == -1)
    {
        write(2, "invalid fd", 11);
        return(0);    
    }
    pipeline->commands[i].input_fd = fd;
    *token = (*token)->next;
    return(1);
}

static int  parse_redir_out(t_pipeline *pipeline, t_token **token, int i)
{
    int fd;

    if (pipeline->commands[i].output_fd != STDOUT_FILENO)
        close(pipeline->commands[i].output_fd);
    fd = open((*token)->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        write(2, "invalid fd", 11);
        return(0);    
    }
    pipeline->commands[i].output_fd = fd;
    *token = (*token)->next;
    return(1);
}

static int  parse_redir_append(t_pipeline *pipeline, t_token **token, int i)
{
    int fd;

    if (pipeline->commands[i].output_fd != STDOUT_FILENO)
        close(pipeline->commands[i].output_fd);
    fd = open((*token)->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        write(2, "invalid fd", 11);
        //check actual error msg
        return(0);    
    }
    pipeline->commands[i].output_fd = fd;
    *token = (*token)->next;
    return(1);
}

static int parse_heredoc(t_pipeline *pipeline, t_token **tokens, int i)
{
    // Heredoc implementation (more complex, typically involves creating a temp file or pipe)
    
    // TODO: Implement heredoc logic
    *tokens = (*tokens)->next;
}

static int parse_redir(t_pipeline *pipeline, t_token **tmp_tokens, int i)
{
    if ((*tmp_tokens)->type == REDIR_IN)
        return(parse_redir_in(pipeline, tmp_tokens, i));
    else if ((*tmp_tokens)->type == REDIR_OUT)
        return(parse_redir_out(pipeline, tmp_tokens, i));
    else if ((*tmp_tokens)->type == REDIR_APPEND)
       return(parse_redir_append(pipeline, tmp_tokens, i));
    else if ((*tmp_tokens)->type == HEREDOC)
        return(parse_heredoc(pipeline, tmp_tokens, i));
    return(1);
}

static int fill_command_helper(t_pipeline **pipeline, t_token *tokens, int count_words, int i)
{
    int j;
    t_token *tmp_tokens;

    j = 0;
    tmp_tokens = tokens;
    (*pipeline)->commands[i].args = malloc(sizeof(char *) * (count_words + 1));
    if (!(*pipeline)->commands[i].args)
            return (0);
    while (j < count_words && tmp_tokens && tmp_tokens->type != T_EOF && tmp_tokens->type != PIPE)
    {
        if (tmp_tokens->type == REDIR_IN || tmp_tokens->type == REDIR_OUT 
                || tmp_tokens->type == REDIR_APPEND || tmp_tokens->type == HEREDOC)
        {
            if (!parse_redir(pipeline, &tmp_tokens, i))
                return (0);
        }
        else if (tmp_tokens->type == WORD)
        {
            (*pipeline)->commands[i].args[j] = ft_strdup(tmp_tokens->value);
            if (!(*pipeline)->commands[i].args[j])
                return (0);
            j++;
        }
        tmp_tokens = tmp_tokens->next;
    }
    (*pipeline)->commands[i].args[j] = NULL;
    return(1);
}

static int fill_command(t_pipeline **pipeline, t_token *tokens)
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
        if(!fill_command_helper(pipeline, cmd_start, count_words, i))
            return (0);
        i++;
        if (tmp_tokens && tmp_tokens->type == PIPE)//is this necessary or can we just go to next
            tmp_tokens = tmp_tokens->next;
    }
    return(1);
}

t_pipeline  *parse(t_token *tokens)
{
    t_pipeline  *pipeline;
    int num_commands;

    if (!syntax_validator(tokens))
        return (NULL);
    num_commands = command_counter(tokens);
    pipeline = initialize_pipeline(num_commands);
    if (!pipeline)
        return (NULL);
    if(!fill_command(&pipeline, tokens))
    {
        free_pipeline(pipeline);
        return (NULL);
    }
    return (pipeline);
}
