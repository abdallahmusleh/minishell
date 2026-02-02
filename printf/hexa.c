/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:57:22 by abmusleh          #+#    #+#             */
/*   Updated: 2025/09/07 21:43:11 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_digit(unsigned long i)
{
	int	num_digits;

	num_digits = 0;
	if (i == 0)
		return (1);
	while (i != 0)
	{
		i = i / 16;
		num_digits++;
	}
	return (num_digits);
}

int	hexadecimal_lower(unsigned int i)
{
	unsigned int	j;
	int				x;
	int				num_digits;
	char			*bases;
	char			hexa_num[16];

	j = 1;
	x = 0;
	bases = "0123456789abcdef";
	while (j <= (i / 16))
		j = j * 16;
	num_digits = num_digit(i);
	while (j > 0)
	{
		hexa_num[x] = bases[(i / j) % 16];
		ft_putchar(hexa_num[x]);
		x++;
		i = i % j;
		j = j / 16;
		num_digits--;
	}
	return (x);
}

int	hexadecimal_upper(unsigned int i)
{
	unsigned int	j;
	int				x;
	int				num_digits;
	char			*bases;
	char			hexa_num[16];

	j = 1;
	x = 0;
	bases = "0123456789ABCDEF";
	while (j <= (i / 16))
		j = j * 16;
	num_digits = num_digit(i);
	while (j > 0)
	{
		hexa_num[x] = bases[(i / j) % 16];
		ft_putchar(hexa_num[x]);
		x++;
		i = i % j;
		j = j / 16;
		num_digits--;
	}
	return (x);
}

static int	hexadecimal_for_voidpointer(unsigned long i)
{
	unsigned long	j;
	int				x;
	int				num_digits;
	char			*bases;
	char			hexa_num[16];

	j = 1;
	x = 0;
	bases = "0123456789abcdef";
	while (j <= (i / 16))
		j = j * 16;
	num_digits = num_digit(i);
	while (j > 0)
	{
		hexa_num[x] = bases[(i / j) % 16];
		ft_putchar(hexa_num[x]);
		x++;
		i = i % j;
		j = j / 16;
		num_digits--;
	}
	return (x);
}

int	voidpointer(unsigned long i)
{
	char	*s;

	if (i == 0)
		return (write(1, "(nil)", 5));
	s = "0x";
	ft_putstr(s);
	return (hexadecimal_for_voidpointer(i) + 2);
}
// int main()
// {
// 	ft_printf("%p",17);
// }