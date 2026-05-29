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

	if (!bench->BUFFER)
		return ;
	tmp = ft_strjoin(bench->BUFFER, op);
	if (!tmp)
	{
		free(bench->BUFFER);
		return ;
	}
	free(bench->BUFFER);
	bench->BUFFER = tmp;
}

void	op_flush(t_bench *bench)
{
	if (bench->BUFFER)
		write(STDOUT_FILENO, bench->BUFFER, ft_strlen(bench->BUFFER));
}
