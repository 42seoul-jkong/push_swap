/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_fast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:02:26 by jkong             #+#    #+#             */
/*   Updated: 2022/04/05 03:48:17 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static size_t	_limit(size_t n)
{
	int	i;

	i = 0;
	while (n >> (i + 1))
		i++;
	return (n * i);
}

ssize_t	_find(t_game *game, t_kind kind, unsigned int r)
{
	size_t	locate;
	t_elem	*elem;
	size_t	count;

	locate = 0;
	elem = game->stack[kind];
	count = game->count[kind];
	while (locate < count && elem->rank != r)
	{
		locate++;
		elem = elem->next;
	}
	if (locate == count)
		return (0);
	else if (locate > count / 2)
		return (locate - count);
	else
		return (locate);
}

void	__test_rot(t_game *game, unsigned int r)
{
	ssize_t	distance;

	distance = _find(game, OF_STACK_B, r);
	if (distance < 0)
	{
		while (distance++ < 0)
			write_op(game, RRB);
	}
	else
	{
		while (distance-- > 0)
			write_op(game, RB);
	}
	write_op(game, PA);
}

int	try_solve_fast(t_game *game)
{
	const size_t	lim = _limit(game->length);
	unsigned int	i;

	if (game->opt_visual)
		visualize("try_solve_fast", game);
	i = game->length;
	while (i-- > 0 && game->op_size < lim)
		write_op(game, PB);
	i = game->length;
	while (i-- > 0 && game->op_size < lim)
		__test_rot(game, i);
	if (game->op_size >= lim)
		return (0);
	if (game->opt_visual)
		visualize("try_solve_fast", game);
	return (1);
}
