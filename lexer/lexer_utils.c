/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:27:36 by abmusleh          #+#    #+#             */
/*   Updated: 2026/02/04 00:46:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *token_list_new(t_token_type type, char *value)
{
    t_token *node;

    node = malloc(sizeof(t_token));
    if (!node)
        return (NULL);
    node->type = type;
    node->value = value;
    node->next = NULL;
    return (node);
}

void	ft_lstadd_back(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!list || !new)
		return ;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

// int	lst_size(t_list *list)
// {
// 	int	i;

// 	i = 1;
// 	if (!list)
// 		return (0);
// 	while (list->next)
// 	{
// 		list = list->next;
// 		i++;
// 	}
// 	return (i);
// }

void	lst_clear(t_token **list)
{
	t_token	*tmp1;
	t_token	*tmp2;

	if (!list || !*list)
		return ;
	tmp1 = *list;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		free((*tmp1)->value);
		free(tmp1);
		tmp1 = tmp2;
	}
	*list = NULL;
}


