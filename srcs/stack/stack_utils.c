/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:51:20 by atajima           #+#    #+#             */
/*   Updated: 2026/05/23 19:19:14 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_push_bottom(t_stack *lst, t_node *node)
{
	if (!lst->bottom)
	{
		lst->top = node;
		lst->bottom = node;
		node->prev = NULL;
		node->next = NULL;
	}
	else
	{
		node->prev = lst->bottom;
		node->next = NULL;
		lst->bottom->next = node;
		lst->bottom = node;
	}
	lst->size++;
}

void	stack_push_top(t_stack *lst, t_node *node)
{
	if (!lst->top)
	{
		lst->top = node;
		lst->bottom = node;
		node->prev = NULL;
		node->next = NULL;
	}
	else
	{
		node->next = lst->top;
		lst->top->prev = node;
		lst->top = node;
	}
	lst->size++;
}

t_node	*stack_pop_top(t_stack *lst)
{
	t_node	*node;

	if (!lst->top)
		return (NULL);
	node = lst->top;
	if (lst->size == 1)
	{
		lst->top = NULL;
		lst->bottom = NULL;
	}
	else
	{
		lst->top = node->next;
		lst->top->prev = NULL;
	}
	node->next = NULL;
	lst->size--;
	return (node);
}
