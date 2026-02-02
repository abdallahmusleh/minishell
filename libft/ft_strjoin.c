/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:27:58 by abmusleh          #+#    #+#             */
/*   Updated: 2025/08/19 21:06:24 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	x;
	char	*newstring;
	int		tot;

	i = 0;
	x = 0;
	if (!s1 || !s2)
		return (NULL);
	tot = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstring = (char *)malloc((tot) * sizeof(char));
	if (!newstring)
		return (NULL);
	while (s1[i])
	{
		newstring[i] = s1[i];
		i++;
	}
	while (s2[x])
	{
		newstring[i + x] = s2[x];
		x++;
	}
	newstring[i + x] = '\0';
	return (newstring);
}

/*int main(void)
{
	char *x = "real ";
	char *y = "madrid";
	printf("%s\n", ft_strjoin(x, y));
}*/
