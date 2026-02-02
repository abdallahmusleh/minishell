/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:49:35 by abmusleh          #+#    #+#             */
/*   Updated: 2025/08/23 21:14:43 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (p[i] == (unsigned char)c)
		{
			return ((void *)&s[i]);
		}
		i++;
	}
	return (NULL);
}
/*#include <string.h>
int	main(void)
{
    //printf("%s\n", (char *)ft_memchr("real madrid", 'd', 20));
	int tab[7] = {-49, 49, 1, -1, 0, -2, 2};
    printf("%s", (char *)memchr(tab, -1, 7));
}*/