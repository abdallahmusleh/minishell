/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:20:21 by abmusleh          #+#    #+#             */
/*   Updated: 2025/08/19 19:57:47 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*z;
	size_t			i;

	i = 0;
	z = (unsigned char *)s;
	while (i < n)
	{
		*z = c;
		i++;
		z++;
	}
	return (s);
}
/*int main()
{
	char str[] = "jana is very";
	printf("%s\n", (char *)ft_memset(str, '7', 5));
}*/
