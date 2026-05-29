/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 19:31:24 by atajima           #+#    #+#             */
/*   Updated: 2026/05/29 20:03:15 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_print(t_bench *bench, char *op)
{
	char	*tmp;

	if (!bench->buffer)
		return ;
	tmp = ft_strjoin(bench->buffer, op);
	if (!tmp)
	{
		free(bench->buffer);
		return ;
	}
	free(bench->buffer);
	bench->buffer = tmp;
}

void	op_flush(t_bench *bench)
{
	if (bench->buffer)
		write(STDOUT_FILENO, bench->buffer, ft_strlen(bench->buffer));
}
