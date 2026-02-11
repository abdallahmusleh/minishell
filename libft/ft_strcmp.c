/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:31:13 by abmusleh          #+#    #+#             */
/*   Updated: 2025/05/02 17:34:10 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		i++;
	}
	if (s1[i] > s2[i])
	{
		return (1);
	}
	else if (s1[i] < s2[i])
	{
		return (-1);
	}
	return (0);
}
/*int main(void)
{
	int x = ft_strcmp("abce", "abca");
	printf ("%d", x);
}
*/
