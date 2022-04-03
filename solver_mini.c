/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:02:26 by jkong             #+#    #+#             */
/*   Updated: 2022/04/04 02:00:47 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	_is_able_to_solve_2(t_game *game, t_kind kind)
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
	const int	a = _is_able_to_solve_2(game, OF_STACK_A);
	const int	b = _is_able_to_solve_2(game, OF_STACK_B);

	if (a && b)
		write_op(game, SS);
	else if (a)
		write_op(game, SA);
	else if (b)
		write_op(game, SB);
}

static t_operation	_suitable_op_only_3(t_game *game, t_kind kind)
{
	const int		rev = kind == OF_STACK_B;
	unsigned int	r0;
	unsigned int	r1;
	unsigned int	r2;

	if (game->count[kind] != 3)
		return (NOP);
	r0 = game->stack[kind]->rank;
	r1 = game->stack[kind]->next->rank;
	r2 = game->stack[kind]->next->next->rank;
	if (((r0 < r1) ^ rev) && ((r1 < r2) ^ rev))
		return (NOP);
	if (((r1 > r0) ^ rev) && ((r1 > r2) ^ rev))
		return (REVERSE | ROTATE);
	else if (((r0 > r1) ^ rev) && (r0 > r2) ^ rev)
		return (ROTATE);
	else
		return (SWAP);
}

void	solve_only_3(t_game *game)
{
	const t_operation	a = _suitable_op_only_3(game, OF_STACK_A);
	const t_operation	b = _suitable_op_only_3(game, OF_STACK_B);

	if (a == b)
	{
		if (a == NOP)
			return ;
		write_op(game, b | FOR_SAME);
	}
	else
	{
		if (a != NOP)
			write_op(game, a | FOR_A);
		if (b != NOP)
			write_op(game, b | FOR_B);
	}
	solve_only_3(game);
}
