/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:39:10 by abmusleh          #+#    #+#             */
/*   Updated: 2025/08/19 19:47:41 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	x;
	char	*string;

	x = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || len == 0)
	{
		return (ft_strdup(""));
	}
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	string = malloc((len + 1) * sizeof(char));
	if (!string)
		return (NULL);
	while (s[start] && x < len)
	{
		string[x] = s[start + x];
		x++;
	}
	string[x] = '\0';
	return (string);
}
// check return c
/*int main()
{
	char const *str = "comment";
	char *u = ft_substr(str, 7, 8);
	printf("%s\n", u);
}*/