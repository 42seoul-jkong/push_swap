/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_qsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:42:57 by jkong             #+#    #+#             */
/*   Updated: 2022/04/05 20:17:45 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	_end(t_game *game, t_kind kind, t_part *parent)
{
	const int	sorted = is_sorted(game, kind, parent);
	const int	len2 = parent->length == 2;
	const int	len3 = parent->length == 3;
	size_t		i;

	if (!(sorted || len2 || len3))
		return (0);
	if (parent->reverse)
	{
		i = parent->length;
		while (i-- > 0)
			write_op(game, op_for_kind(kind, REVERSE | ROTATE));
	}
	if (len3)
		solve_3(game, kind);
	else if (len2)
		solve_2(game, kind);
	else if (kind == OF_STACK_B)
	{
		i = parent->length;
		while (i-- > 0)
			write_op(game, PA);
	}
	return (1);
}

static void	_half_part(t_part *parent, t_part child[STACK_KIND_N])
{
	const size_t	half_length = parent->length / 2;

	child[OF_STACK_B].start = parent->start;
	child[OF_STACK_B].length = half_length;
	child[OF_STACK_B].reverse = 0;
	child[OF_STACK_A].start = parent->start + half_length;
	child[OF_STACK_A].length = parent->length - half_length;
	child[OF_STACK_A].reverse = 0;
}

static int	_exact_half(t_game *game, t_kind kind, t_part *inverse)
{
	t_elem			*elem;
	size_t			i;

	elem = game->stack[kind];
	i = inverse->length;
	if (i > game->count[kind])
		return (0);
	while (i-- > 0)
	{
		if (!contains_part(inverse, elem->rank))
		{
			if (!(i == 0 && contains_part(inverse, elem->next->rank)))
				return (0);
		}
		elem = elem->next;
	}
	i = inverse->length;
	while (i-- > 0)
	{
		if (i == 0)
			try_swap(game, kind);
		write_op(game, op_for_kind(inverse_kind(kind), PUSH));
	}
	return (1);
}

static void	_qsort_partition(t_game *game, t_kind kind, t_part *parent)
{
	size_t		i;
	t_part		child[STACK_KIND_N];
	t_part		*inverse;

	if (_end(game, kind, parent))
		return ;
	i = parent->length;
	_half_part(parent, child);
	inverse = &child[inverse_kind(kind)];
	if (!(!parent->reverse && _exact_half(game, kind, inverse)))
	{
		while (i-- > 0)
		{
			if (parent->reverse)
				write_op(game, op_for_kind(kind, REVERSE | ROTATE));
			if (contains_part(inverse, game->stack[kind]->rank))
				write_op(game, op_for_kind(inverse_kind(kind), PUSH));
			else if (!parent->reverse)
				write_op(game, op_for_kind(kind, ROTATE));
		}
		if (!parent->reverse)
			child[kind].reverse = game->count[kind] != child[kind].length;
	}
	_qsort_partition(game, OF_STACK_A, &child[OF_STACK_A]);
	_qsort_partition(game, OF_STACK_B, &child[OF_STACK_B]);
}

void	solve_qsort(t_game *game)
{
	t_part	root;

	root.start = 0;
	root.length = game->length;
	root.reverse = 0;
	_qsort_partition(game, OF_STACK_A, &root);
}
