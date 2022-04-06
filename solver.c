/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:52 by jkong             #+#    #+#             */
/*   Updated: 2022/04/06 02:45:42 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	_put_op(t_operation op)
{
	if (op == SA)
		putstr_safe("sa\n");
	else if (op == SB)
		putstr_safe("sb\n");
	else if (op == SS)
		putstr_safe("ss\n");
	else if (op == PA)
		putstr_safe("pa\n");
	else if (op == PB)
		putstr_safe("pb\n");
	else if (op == RA)
		putstr_safe("ra\n");
	else if (op == RB)
		putstr_safe("rb\n");
	else if (op == RR)
		putstr_safe("rr\n");
	else if (op == RRA)
		putstr_safe("rra\n");
	else if (op == RRB)
		putstr_safe("rrb\n");
	else if (op == RRR)
		putstr_safe("rrr\n");
}

static void	_optimize(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < game->op_size)
	{
		if (game->op_vector[i] & ROTATE)
		{
			j = i;
			while (j < game->op_size)
			{
				if (game->op_vector[j] == (REVERSE ^ game->op_vector[i]))
				{
					game->op_vector[i] = NOP;
					game->op_vector[j] = NOP;
					game->op_optimize += 2;
					break ;
				}
				else if (game->op_vector[j] != game->op_vector[i])
					break ;
				j++;
			}
		}
		i++;
	}
}

void	write_op(t_game *game, t_operation op)
{
	const size_t	capacity = game->op_capacity;
	t_operation		*detach;
	t_operation		*attach;

	if (capacity <= game->op_size)
	{
		detach = game->op_vector;
		attach = calloc_safe(capacity + VECTOR_SIZE, sizeof(*attach));
		if (detach)
			ft_memcpy(attach, detach, capacity * sizeof(t_operation));
		free(detach);
		game->op_vector = attach;
		game->op_capacity += VECTOR_SIZE;
	}
	game->op_vector[game->op_size++] = op;
	apply_op(game, op);
}

void	run_solver(t_game *game)
{
	size_t	i;

	if (game->opt_visual)
		visualize("run_solver", game);
	solve_qsort(game);
	_optimize(game);
	i = 0;
	while (i < game->op_size)
		_put_op(game->op_vector[i++]);
	if (game->opt_visual)
	{
		if (is_sort_completed(game))
			visualize("Diff OK :)", game);
		else
			visualize("Not implemented. KO :(", game);
	}
}
