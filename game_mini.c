/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:02:26 by jkong             #+#    #+#             */
/*   Updated: 2022/03/31 15:14:33 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	_do_game_2(t_game *game, t_stack_type type)
{
	const int		rev = type == OF_STACK_B;
	t_operation		op;
	unsigned int	r0;
	unsigned int	r1;

	if (game->count[type] < 2)
		return ;
	r0 = game->stack[type]->rank;
	r1 = game->stack[type]->next->rank;
	if ((r0 < r1) ^ rev)
		return ;
	op = SWAP;
	if (type == OF_STACK_A)
		op |= FOR_A;
	else if (type == OF_STACK_B)
		op |= FOR_B;
	write_op(game, op);
}

static void	_do_game_3(t_game *game, t_stack_type type)
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
	if (type == OF_STACK_A)
		op |= FOR_A;
	else if (type == OF_STACK_B)
		op |= FOR_B;
	write_op(game, op);
	_do_game_3(game, type);
}

/*
** DEPRECATED
*/
void	do_game_mini(t_game *game)
{
	unsigned int	i;

	if (game->length == 3)
	{
		_do_game_3(game, OF_STACK_A);
		visualize("FIRST", game);
		return ;
	}
	_do_game_2(game, OF_STACK_A);
	visualize("SECOND", game);
	i = 0;
	while (i < game->length)
	{
		if (game->stack[OF_STACK_A]->rank < game->length / 2)
			write_op(game, PB);
		else
			write_op(game, RA);
		i++;
	}
	visualize("THIRD", game);
	_do_game_2(game, OF_STACK_A);
	_do_game_2(game, OF_STACK_B);
	visualize("FOURTH", game);
}
