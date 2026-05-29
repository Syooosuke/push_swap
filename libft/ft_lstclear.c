/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syokota <syokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 10:23:03 by syokota           #+#    #+#             */
/*   Updated: 2026/04/26 10:27:51 by syokota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next_node;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next_node = current->next;
		ft_lstdelone(current, del);
		current = next_node;
	}
	*lst = NULL;
}
