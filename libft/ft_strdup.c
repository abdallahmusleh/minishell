/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:27:37 by abmusleh          #+#    #+#             */
/*   Updated: 2025/08/14 20:22:34 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*mal;
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (s[i])
		i++;
	mal = malloc((i + 1) * sizeof(char));
	if (!mal)
		return (NULL);
	while (s[x])
	{
		mal[x] = s[x];
		x++;
	}
	mal[x] = '\0';
	return (mal);
}
