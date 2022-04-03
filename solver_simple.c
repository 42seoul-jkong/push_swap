/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:02:26 by jkong             #+#    #+#             */
/*   Updated: 2022/04/04 02:27:26 by jkong            ###   ########.fr       */
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

int	try_solve_simple(t_game *game)
{
	const size_t	lim = _limit(game->length);
	unsigned int	i;

	if (game->opt_visual)
		visualize("try_solve_simple", game);
	i = game->length;
	while (i-- > 0)
	{
		if (game->stack[OF_STACK_A]->rank < game->length / 2)
			write_op(game, PB);
		else
			write_op(game, RA);
		i++;
	}
	if (game->op_size >= lim)
		return (0);
	return (1);
}
