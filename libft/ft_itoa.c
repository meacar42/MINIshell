/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meacar <meacar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:34:14 by meacar            #+#    #+#             */
/*   Updated: 2023/07/18 15:34:15 by meacar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_len(long src)
{
	int	i;

	i = 0;
	if (src == 0)
		return (1);
	if (src < 0)
		i++;
	while (src)
	{
		src /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	num;

	num = n;
	i = ft_len(num);
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		num *= -1;
		str[0] = '-';
	}
	str[i] = 0;
	i--;
	while (i >= (n < 0))
	{
		str[i] = (num % 10) + '0';
		num /= 10;
		i--;
	}
	return (str);
}
