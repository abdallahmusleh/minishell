/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:56:36 by abmusleh          #+#    #+#             */
/*   Updated: 2025/08/19 19:59:29 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*newstring;

	i = 0;
	if (!s || !f)
		return (NULL);
	newstring = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!newstring)
		return (NULL);
	while (s[i])
	{
		newstring[i] = f(i, s[i]);
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
/*char ft_toupper(unsigned int i, char c)
{
	(void)i;
	if (c > 96 && c < 123)
	{
		c = c - 32;
	}
	return (c);
}
int	main(void)
{
	int i;
	i = 0;
	char const *str = "real";
	printf("%s\n", ft_strmapi(str, ft_toupper));
}*/
