/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syokota <syokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 19:51:13 by syokota           #+#    #+#             */
/*   Updated: 2026/05/01 15:27:33 by syokota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static void	*free_all(char **strs, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static char	**allocate_word(char const *s, char c, char **strs)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != '\0' && s[i] != c)
				i++;
			strs[j] = ft_substr(s, start, i - start);
			if (!strs[j])
				return (free_all(strs, j));
			j++;
		}
		else
			i++;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (NULL);
	strs = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!strs)
		return (NULL);
	return (allocate_word(s, c, strs));
}
