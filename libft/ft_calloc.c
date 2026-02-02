/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmusleh <abmusleh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:15:55 by abmusleh          #+#    #+#             */
/*   Updated: 2025/08/17 18:27:45 by abmusleh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*temp;
	void			*c;
	size_t			i;
	size_t			huge;

	huge = nmemb * size;
	if (nmemb == 0 || size == 0)
	{
		c = (char *)malloc(sizeof(char) * 1);
		if (c == NULL)
			return (NULL);
		return (c);
	}
	if (huge / size != nmemb)
		return (NULL);
	temp = malloc(huge);
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (i < huge)
	{
		temp[i] = 0;
		i++;
	}
	return (temp);
}
/*int main(void)
{
    int *arr = ft_calloc(5, sizeof(int)); // 5 integers, each initialized to 0
    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        return (1);
    }

    for (int i = 0; i < 5; i++)
        printf("arr[%d] = %d\n", i, arr[i]); // Should print: arr[0] = 0,
	arr[1] = 0, ...

    free(arr); // Don't forget to free the memory
    return (0);
}*/