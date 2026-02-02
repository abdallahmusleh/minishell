/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:57:49 by abmusleh          #+#    #+#             */
/*   Updated: 2025/08/18 20:49:04 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(long n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

void	fill_arr(int i, char *num, long j)
{
	if (j < 0)
	{
		num[0] = '-';
		j = -j;
	}
	num[i] = '\0';
	i--;
	while (j != 0)
	{
		num[i] = ((j % 10) + '0');
		j = j / 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	char	*num;
	int		i;
	long	j;

	j = n;
	i = count(j);
	num = malloc((i + 1) * sizeof(char));
	if (!num)
		return (NULL);
	if (j == 0)
	{
		num[0] = '0';
		num[1] = '\0';
		return (num);
	}
	fill_arr(i, num, j);
	return (num);
}
// int main()
// {
// 	printf("%s\n", ft_itoa(-2147483648));
// }
