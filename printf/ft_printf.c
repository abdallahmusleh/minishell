/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:35:02 by abmusleh          #+#    #+#             */
/*   Updated: 2025/09/08 15:17:36 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	reader(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'i' || c == 'd')
		count += ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		count += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (c == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (c == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (c == '%')
		count += write(1, "%", 1);
	else if (c == 'x')
		count += hexadecimal_lower(va_arg(args, unsigned int));
	else if (c == 'X')
		count += hexadecimal_upper(va_arg(args, unsigned int));
	else if (c == 'p')
		count += voidpointer(va_arg(args, unsigned long));
	return (count);
}

int	ft_printf(const char *placeholders, ...)
{
	size_t	i;
	va_list	args;
	int		count;

	i = 0;
	count = 0;
	if (!placeholders)
		return (-1);
	va_start(args, placeholders);
	while (placeholders[i])
	{
		if (placeholders[i] == '%')
		{
			i++;
			count += reader(placeholders[i], args);
		}
		else
			count += write(1, &placeholders[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
// int	main(void)
// {
// 	int x = ft_printf("%sss\n", "blabla");
// 	ft_printf("%d\n", x);
// 	int y = printf("%sss\n", "blabla");
// 	printf("%d\n", y);
// }