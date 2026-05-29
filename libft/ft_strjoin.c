/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syokota <syokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:51:53 by syokota           #+#    #+#             */
/*   Updated: 2026/04/25 19:01:28 by syokota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	total_len;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	joined = malloc(sizeof(char) * (total_len + 1));
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, s1, total_len + 1);
	ft_strlcat(joined, s2, total_len + 1);
	return (joined);
}
