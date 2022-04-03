/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:02:26 by jkong             #+#    #+#             */
/*   Updated: 2022/04/03 17:50:43 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_able_to_solve_2(t_game *game, t_kind kind)
{
	const int		rev = kind == OF_STACK_B;
	unsigned int	r0;
	unsigned int	r1;

	if (game->count[kind] < 2)
		return (0);
	r0 = game->stack[kind]->rank;
	r1 = game->stack[kind]->next->rank;
	if ((r0 < r1) ^ rev)
		return (0);
	return (1);
}

void	solve_2(t_game *game)
{
	int	a;
	int	b;

	a = is_able_to_solve_2(game, OF_STACK_A);
	b = is_able_to_solve_2(game, OF_STACK_B);
	if (a && b)
		write_op(game, SS);
	else if (a)
		write_op(game, SA);
	else if (b)
		write_op(game, SB);
}

void	solve_only_3(t_game *game, t_kind kind)
{
	const int		rev = kind == OF_STACK_B;
	t_operation		op;
	unsigned int	r0;
	unsigned int	r1;
	unsigned int	r2;

	if (game->count[kind] != 3)
		return ;
	r0 = game->stack[kind]->rank;
	r1 = game->stack[kind]->next->rank;
	r2 = game->stack[kind]->next->next->rank;
	if (((r0 < r1) ^ rev) && ((r1 < r2) ^ rev))
		return ;
	if (((r1 > r0) ^ rev) && ((r1 > r2) ^ rev))
		op = REVERSE | ROTATE;
	else if (((r0 > r1) ^ rev) && (r0 > r2) ^ rev)
		op = ROTATE;
	else
		op = SWAP;
	write_op(game, op_for_kind(kind, op));
	solve_only_3(game, kind);
}

int	do_game_mini(t_game *game)
{
	unsigned int	i;

	if (game->length > STACK_KIND_N * MINI_LIMIT)
		return (0);
	if (game->length > MINI_LIMIT)
	{
		i = 0;
		while (i < game->length)
		{
			if (game->stack[OF_STACK_A]->rank < game->length / 2)
				write_op(game, PB);
			else
				write_op(game, RA);
			i++;
		}
	}
	solve_only_3(game, OF_STACK_A);
	solve_only_3(game, OF_STACK_B);
	solve_2(game);
	i = game->count[OF_STACK_B];
	while (i-- > 0)
		write_op(game, PA);
	if (game->opt_visual)
		visualize("do_game_mini", game);
	return (1);
}
