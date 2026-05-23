/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atajima <atajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 19:57:33 by syokota           #+#    #+#             */
/*   Updated: 2026/05/23 15:42:33 by atajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	int				value;
	int				rank;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef enum e_strategy
{
	START_SIMPLE,
	START_MEDIUM,
	START_COMPLEX,
	START_ADAPTIVE
}				t_strategy;

typedef struct s_stack
{
	t_node	*top;
	t_node	*bottom;
	int		size;
}	t_stack;

typedef struct s_bench
{
	int			enabled;
	double		disorder;
	t_strategy	strategy_used;
	int count_sa; 
	int	count_sb;
	int	count_ss;
	int count_pa;
	int	count_pb;
	int count_ra;
	int	count_rb;
	int	count_rr;
	int count_rra;
	int	count_rrb;
	int	count_rrr;
}	t_bench;


int				parse_args(int argc, char **argv, t_stack *a, t_strategy *strat,
					t_bench *bench);
void			error_exit(void);

t_stack			*stack_init(int capacity);
void			stack_free(t_stack *s);

#endif
