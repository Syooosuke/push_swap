/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:15:32 by atajima           #+#    #+#             */
/*   Updated: 2026/05/23 17:48:37 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_free(t_stack *lst)
{
	t_node	*current;
	t_node	*next;

	if (!lst)
		return ;
	current = lst->top;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(lst);
}
