/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:02:26 by jkong             #+#    #+#             */
/*   Updated: 2022/04/05 17:39:33 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static void	_solve_only_3(t_game *game)
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
	_solve_only_3(game);
}

static void	_solve_3_a(t_game *game)
{
	try_swap(game, OF_STACK_A);
	write_op(game, RA);
	try_swap(game, OF_STACK_A);
	write_op(game, RRA);
	try_swap(game, OF_STACK_A);
}

static void	_solve_3_b(t_game *game)
{
	const int		rev = 1;
	unsigned int	r0;
	unsigned int	r1;
	unsigned int	r2;
	int				rot;

	r0 = game->stack[OF_STACK_B]->rank;
	r1 = game->stack[OF_STACK_B]->next->rank;
	r2 = game->stack[OF_STACK_B]->next->next->rank;
	rot = (r2 < r0) ^ rev && (r2 < r1) ^ rev;
	if (rot)
		write_op(game, RB);
	try_swap(game, OF_STACK_B);
	write_op(game, PA);
	if (rot)
		write_op(game, RRB);
	try_swap(game, OF_STACK_B);
	write_op(game, PA);
	write_op(game, PA);
}

void	solve_3(t_game *game, t_kind kind)
{
	if (game->count[kind] == 3)
	{
		_solve_only_3(game);
		if (kind == OF_STACK_B)
		{
			write_op(game, PA);
			write_op(game, PA);
			write_op(game, PA);
		}
	}
	else if (kind == OF_STACK_A)
		_solve_3_a(game);
	else if (kind == OF_STACK_B)
		_solve_3_b(game);
}
