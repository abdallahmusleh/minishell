/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:10:58 by abmusleh          #+#    #+#             */
/*   Updated: 2025/08/24 14:28:45 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countword(char const *s, char c)
{
	int		flag;
	int		count;
	size_t	i;

	flag = 1;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 1)
		{
			count++;
			flag = 0;
		}
		if (s[i] == c && flag == 0)
			flag = 1;
		i++;
	}
	return (count);
}

static char	**free1(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static char	*word(char *s, char c)
{
	int		i;
	int		x;
	char	*word;

	i = 0;
	x = 0;
	while (s[i] != c && s[i])
		i++;
	word = malloc((i + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (s[x] && s[x] != c)
	{
		word[x] = s[x];
		x++;
	}
	word[x] = '\0';
	return (word);
}

int	nullchecker(size_t *i, size_t *count, const char *s)
{
	*i = 0;
	*count = 0;
	if (!s)
		return (-1);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	count;
	char	**array;

	if (nullchecker(&i, &count, s) == -1)
		return (NULL);
	array = malloc((countword(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array[countword(s, c)] = NULL;
	while (i < ft_strlen(s))
	{
		if (s[i] == c)
			i++;
		else
		{
			array[count] = word((char *)&s[i], c);
			if (!array[count])
				return (free1(array));
			while (s[i] != c && s[i])
				i++;
			count++;
		}
	}
	return (array);
}
/*int	main(void)
{
	int i = 0;
	char **s = ft_split("lorem ipsum dolor sit amet,
			consectetur adipiscing elit. Sed non risus. Suspendisse", ' ');
	while (s[i])
	{
		printf("%s\n", s[i]);
		i++;
	}
}*/