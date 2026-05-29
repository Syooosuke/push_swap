/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syokota <syokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:52:44 by syokota           #+#    #+#             */
/*   Updated: 2026/05/03 15:31:17 by syokota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total;

	if (count != 0 && size > (size_t)-1 / count)
		return (NULL);
	total = size * count;
	ptr = malloc(total);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}
