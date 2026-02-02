/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:34:22 by abmusleh          #+#    #+#             */
/*   Updated: 2025/08/23 20:04:15 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*c;
	unsigned char	*x;
	size_t			i;

	c = (unsigned char *)dest;
	x = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		c[i] = x[i];
		i++;
	}
	return (dest);
}
