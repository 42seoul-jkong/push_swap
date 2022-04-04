/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:02:26 by jkong             #+#    #+#             */
/*   Updated: 2022/04/04 12:57:04 by jkong            ###   ########.fr       */
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

void	_find(t_game *game, unsigned int r)
{
	unsigned int	locate;
	t_elem			*elem;

	locate = 0;
	elem = game->stack[OF_STACK_B];
	while (locate < game->count[OF_STACK_B])
	{
		if (elem->rank == r)
			break ;
		locate++;
		elem = elem->next;
	}
	while (locate-- > 0)
		write_op(game, RB);
	write_op(game, PA);
}

int	try_solve_simple(t_game *game)
{
	const size_t	lim = _limit(game->length);
	unsigned int	i;

	if (game->opt_visual)
		visualize("try_solve_simple", game);
	i = game->length;
	while (i-- > 0 && game->op_size < lim)
		write_op(game, PB);
	i = game->length;
	while (i-- > 0 && game->op_size < lim)
		_find(game, i);
	if (game->op_size >= lim)
		return (0);
	if (game->opt_visual)
		visualize("try_solve_simple", game);
	return (1);
}
