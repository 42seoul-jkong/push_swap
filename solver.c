/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:52 by jkong             #+#    #+#             */
/*   Updated: 2022/04/03 18:30:35 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	_put_op(t_operation op)
{
	char	c;

	if (op & SWAP)
		c = 's';
	else if (op & PUSH)
		c = 'p';
	else if (op & ROTATE)
		c = 'r';
	else
		return ;
	if (op & REVERSE)
		putchar_safe('r');
	putchar_safe(c);
	if ((op & FOR_A) && (op & FOR_B))
		putchar_safe(c);
	else if (op & FOR_A)
		putchar_safe('a');
	else if (op & FOR_B)
		putchar_safe('b');
	putchar_safe('\n');
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

#ifdef __DEBUG
	(void)capacity, (void)detach, (void)attach;
	_put_op(op);
	game->op_size++;
#else
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
#endif
	apply_op(game, op);
}

void	run_solver(t_game *game)
{
	size_t	i;

	if (!is_sort_completed(game) && !solve_mini(game))
	{
		solve_qsort(game);
	}
#ifndef __DEBUG
	_optimize(game);
	i = 0;
	while (i < game->op_size)
		_put_op(game->op_vector[i++]);
#else
	if (i = 0, i)
		_optimize(game);
#endif
	if (game->opt_visual)
		visualize("Not implemented. KO :(", game);
}
