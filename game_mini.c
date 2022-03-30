/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:02:26 by jkong             #+#    #+#             */
/*   Updated: 2022/03/31 03:20:48 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	do_game_2(t_game *game, t_stack_type type)
{
	t_operation		op;
	unsigned int	r0;
	unsigned int	r1;

	if (game->count[type] != 2)
		return ;
	r0 = game->stack[type]->rank;
	r1 = game->stack[type]->next->rank;
	if ((r0 < r1) ^ (type == OF_STACK_B))
		return ;
	op = SWAP;
	if (type == OF_STACK_A)
		op |= FOR_A;
	else if (type == OF_STACK_B)
		op |= FOR_B;
	write_op(game, op);
}

static void	do_game_3a(t_game *game)
{
	t_operation		op;
	unsigned int	r0;
	unsigned int	r1;
	unsigned int	r2;

	if (game->count[OF_STACK_A] != 3)
		return ;
	r0 = game->stack[OF_STACK_A]->rank;
	r1 = game->stack[OF_STACK_A]->next->rank;
	r2 = game->stack[OF_STACK_A]->next->next->rank;
	if (r0 < r1 && r1 < r2)
		return ;
	if (r0 < r1)
		op = RRA;
	else if (r0 > r2)
		op = RA;
	else
		op = SA;
	write_op(game, op);
	do_game_3a(game);
}

static void	do_game_3b(t_game *game)
{
	t_operation		op;
	unsigned int	r0;
	unsigned int	r1;
	unsigned int	r2;

	if (game->count[OF_STACK_B] != 3)
		return ;
	r0 = game->stack[OF_STACK_B]->rank;
	r1 = game->stack[OF_STACK_B]->next->rank;
	r2 = game->stack[OF_STACK_B]->next->next->rank;
	if (r0 > r1 && r1 > r2)
		return ;
	if (r0 < r1)
		op = RB;
	else if (r1 > r2)
		op = RRB;
	else
		op = SB;
	write_op(game, op);
	do_game_3b(game);
}

/*
** DEPRECATED
*/
void	do_game_mini(t_game *game)
{
	unsigned int	i;

	visualize("FIRST", game);
	do_game_2(game, OF_STACK_A);
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
	if (game->count[OF_STACK_A] >= 2)
	{
		i = game->stack[OF_STACK_A]->next->rank;
		if (game->stack[OF_STACK_A]->rank > i)
			write_op(game, SA);
	}
	if (game->count[OF_STACK_B] >= 2)
	{
		i = game->stack[OF_STACK_B]->next->rank;
		if (game->stack[OF_STACK_B]->rank > i)
			write_op(game, SB);
	}
	visualize("FOURTH", game);
}
