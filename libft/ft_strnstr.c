/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:49:40 by abmusleh          #+#    #+#             */
/*   Updated: 2025/08/23 19:31:18 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	tmp;
	int		x;
	size_t	j;

	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[j] && j < len)
	{
		tmp = j;
		x = 0;
		while (big[tmp] && little[x] && (big[tmp] == little[x]) && tmp < len)
		{
			x++;
			tmp++;
		}
		if (little[x] == '\0')
			return ((char *)&big[j]);
		j++;
	}
	return (0);
}
// int main()
// {
//     printf("%s\n", ft_strnstr("bimg man ting", "mann", 7));
// }
