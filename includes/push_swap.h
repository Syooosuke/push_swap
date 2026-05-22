/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syokota <syokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 19:57:33 by syokota           #+#    #+#             */
/*   Updated: 2026/05/22 20:08:20 by syokota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int			*data;
	int			*rank;
	int			size;
	int			capacity;
}				t_stack;

typedef enum e_strategy
{
	START_SIMPLE,
	START_MEDIUM,
	START_COMPLEX,
	START_ADAPTIVE
}				t_strategy;

typedef struct s_bench
{
	int			enabled;
	double		disorder;
	t_strategy	strategy_used;
	int count_sa, count_sb, count_ss;
	int count_pa, count_pb;
	int count_ra, count_rb, count_rr;
	int count_rra, count_rrb, count_rrr;
}				t_bench;

int				parse_args(int argc, char **argv, t_stack *a, t_strategy *strat,
					t_bench *bench);
void			error_exit(void);

t_stack			*stack_init(int capacity);
void			stack_free(t_stack *s);

#endif
