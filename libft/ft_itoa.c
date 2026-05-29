/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syokota <syokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 20:42:34 by syokota           #+#    #+#             */
/*   Updated: 2026/05/01 15:58:04 by syokota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digits(long n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
	{
		count = 1;
		n = -n;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	num;

	num = n;
	len = get_digits(num);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num == 0)
		str[0] = '0';
	else if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		len--;
		str[len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
