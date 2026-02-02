/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:52:51 by abmusleh          #+#    #+#             */
/*   Updated: 2025/08/23 21:18:26 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_num;
	size_t	temp;

	i = 0;
	src_num = 0;
	temp = 0;
	while (src[src_num])
		src_num++;
	while (dst[i])
		i++;
	if (size <= i)
		return (size + src_num);
	else
	{
		while (src[temp] && i + temp < size - 1)
		{
			dst[i + temp] = src[temp];
			temp++;
		}
		dst[i + temp] = '\0';
		return (i + src_num);
	}
}
// int main()
// {
//     char d[8] = "abcdef";
//     char *s = "shatha";
//     printf("%d\n", ft_strlcat(d, "123", 0));
//     printf("%s\n", d);
// }