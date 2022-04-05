/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_micro.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:02:26 by jkong             #+#    #+#             */
/*   Updated: 2022/04/05 17:47:14 by jkong            ###   ########.fr       */
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

void	solve_2(t_game *game, t_kind kind)
{
	const int	a = _is_able_to_solve_2(game, OF_STACK_A);
	const int	b = _is_able_to_solve_2(game, OF_STACK_B);

	if (a && b)
		write_op(game, SS);
	else if (a)
		write_op(game, SA);
	else if (b)
		write_op(game, SB);
	if (kind == OF_STACK_B)
	{
		write_op(game, PA);
		write_op(game, PA);
	}
}

void	try_swap(t_game *game, t_kind kind)
{
	if (_is_able_to_solve_2(game, kind))
		write_op(game, op_for_kind(kind, SWAP));
}

int	half_4(t_game *game, t_kind kind, t_part *inverse)
{
	unsigned int	r0;
	unsigned int	r1;
	unsigned int	r2;
	unsigned int	r3;

	r0 = game->stack[kind]->rank;
	r1 = game->stack[kind]->next->rank;
	r2 = game->stack[kind]->next->next->rank;
	r3 = game->stack[kind]->next->next->next->rank;
	(void)r1;
	if (!contains_part(inverse, r0))
		return (0);
	if (contains_part(inverse, r3))
		return (0);
	write_op(game, op_for_kind(inverse_kind(kind), PUSH));
	if (contains_part(inverse, r2))
		write_op(game, op_for_kind(kind, SWAP));
	write_op(game, op_for_kind(inverse_kind(kind), PUSH));
	return (1);
}
