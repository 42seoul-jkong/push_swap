/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:02:26 by jkong             #+#    #+#             */
/*   Updated: 2022/04/02 19:29:07 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_operation	_for_type(t_stack_type type, t_operation op)
{
	if (type == OF_STACK_A)
		op |= FOR_A;
	if (type == OF_STACK_B)
		op |= FOR_B;
	return (op);
}

void	do_game_2(t_game *game, t_stack_type type)
{
	const int		rev = type == OF_STACK_B;
	unsigned int	r0;
	unsigned int	r1;

	if (game->count[type] < 2)
		return ;
	r0 = game->stack[type]->rank;
	r1 = game->stack[type]->next->rank;
	if ((r0 < r1) ^ rev)
		return ;
	write_op(game, _for_type(type, SWAP));
}

void	do_game_3(t_game *game, t_stack_type type)
{
	const int		rev = type == OF_STACK_B;
	t_operation		op;
	unsigned int	r0;
	unsigned int	r1;
	unsigned int	r2;

	if (game->count[type] != 3)
		return ;
	r0 = game->stack[type]->rank;
	r1 = game->stack[type]->next->rank;
	r2 = game->stack[type]->next->next->rank;
	if (((r0 < r1) ^ rev) && ((r1 < r2) ^ rev))
		return ;
	if (((r1 > r0) ^ rev) && ((r1 > r2) ^ rev))
		op = REVERSE | ROTATE;
	else if (((r0 > r1) ^ rev) && (r0 > r2) ^ rev)
		op = ROTATE;
	else
		op = SWAP;
	write_op(game, _for_type(type, op));
	do_game_3(game, type);
}

static void	_half(t_game *game)
{
	unsigned int	i;

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

int	do_game_mini(t_game *game)
{
	unsigned int	i;

	if (game->length > STACK_TYPE_N * MINI_LIMIT)
		return (0);
	if (game->length > MINI_LIMIT)
		_half(game);
	do_game_3(game, OF_STACK_A);
	do_game_3(game, OF_STACK_B);
	do_game_2(game, OF_STACK_A);
	do_game_2(game, OF_STACK_B);
	i = game->count[OF_STACK_B];
	while (i-- > 0)
		write_op(game, PA);
	if (game->opt_visual)
		visualize("do_game_mini", game);
	return (1);
}
