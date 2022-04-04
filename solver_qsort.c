/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_qsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:42:57 by jkong             #+#    #+#             */
/*   Updated: 2022/04/05 00:00:53 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#ifdef __DEBUG
		#include <stdio.h>
		#include <stdarg.h>

		static int __depth;

		static char *__format(char *format, ...)
		{
			static char dest[4096];
			va_list va;
			va_start(va, format);
			vsprintf(dest, format, va);
			va_end(va);
			return dest;
		}
#endif

static int	_end(t_game *game, t_kind kind, t_part *parent)
{
	const int	already = is_sorted(game, kind, parent);
	const int	len2 = parent->length <= 2;
	const int	only3 = parent->length == 3 && game->count[kind] == 3;
	size_t		i;

	if (!(already || len2 || only3))
		return (0);
	if (parent->reverse)
	{
		i = parent->length;
		while (i-- > 0)
			write_op(game, op_for_kind(kind, REVERSE | ROTATE));
	}
	if (only3)
		solve_only_3(game);
	else if (len2)
		solve_2(game);
	if (kind == OF_STACK_B)
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

static int	_contains_part(t_part *part, unsigned int rank)
{
	const unsigned int	start = part->start;
	const unsigned int	end = start + part->length;

	return (start <= rank && rank < end);
}

/*
** Deprecated cause Duplicated
*/
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

static int	_simple3(t_game *game, t_kind kind, t_part *parent)
{
	const int		rev = kind == OF_STACK_B;
	unsigned int	r0;
	unsigned int	r1;
	unsigned int	r2;
	size_t			i;

	if (parent->length != 3)
		return (0);
	if (!parent->reverse)
	{
		r0 = game->stack[kind]->rank;
		r1 = game->stack[kind]->next->rank;
		r2 = game->stack[kind]->next->next->rank;
	}
	else
	{
		r0 = game->stack[kind]->prev->prev->prev->rank;
		r1 = game->stack[kind]->prev->prev->rank;
		r2 = game->stack[kind]->prev->rank;
	}
#ifdef __DEBUG
			visualize(__format("SIMPLE_THREE You can't optimize this three? (SUCCESS = %d) in %c, (%u, %zu / R = %d) %u %u %u\n",
			!((r0 > r1) ^ rev && (r1 > r2) ^ rev),
			'A' + kind,
			parent->start, parent->length, parent->reverse,
			r0, r1, r2), game);
#endif
	if ((r0 > r1) ^ rev && (r1 > r2) ^ rev)
		return (0);
	if (parent->reverse)
	{
		i = parent->length;
		while (i-- > 0)
			write_op(game, op_for_kind(kind, REVERSE | ROTATE));
	}
	if (_is_able_to_solve_2(game, kind))
		write_op(game, op_for_kind(kind, SWAP));
	write_op(game, op_for_kind(kind, ROTATE));
	if (_is_able_to_solve_2(game, kind))
		write_op(game, op_for_kind(kind, SWAP));
	write_op(game, op_for_kind(kind, REVERSE | ROTATE));
	if (_is_able_to_solve_2(game, kind))
		write_op(game, op_for_kind(kind, SWAP));
	if (kind == OF_STACK_B)
	{
		i = parent->length;
		while (i-- > 0)
			write_op(game, PA);
	}
	return (1);
}

static int	_smart4(t_game *game, t_kind kind, t_part *parent, t_part child[STACK_KIND_N])
{
	unsigned int	r0;
	unsigned int	r1;
	unsigned int	r2;
	unsigned int	r3;

	if (parent->length != 4 || parent->reverse)
		return (0);
	r0 = game->stack[kind]->rank;
	r1 = game->stack[kind]->next->rank;
	r2 = game->stack[kind]->next->next->rank;
	r3 = game->stack[kind]->next->next->next->rank;
#ifdef __DEBUG
			visualize(__format("SMART_FOUR You can't optimize this four? (SUCCESS = %d) in %c, (%u, %zu / %u, %zu) %u %u %u %u\n",
			!(!_contains_part(&child[inverse_kind(kind)], r0) || _contains_part(&child[inverse_kind(kind)], r3)),
			'A' + kind,
			child[OF_STACK_A].start, child[OF_STACK_A].length,
			child[OF_STACK_B].start, child[OF_STACK_B].length,
			r0, r1, r2, r3), game);
#endif
	(void)r1;
	if (!_contains_part(&child[inverse_kind(kind)], r0))
		return (0);
	if (_contains_part(&child[inverse_kind(kind)], r3))
		return (0);
	write_op(game, op_for_kind(inverse_kind(kind), PUSH));
	if (_contains_part(&child[inverse_kind(kind)], r2))
		write_op(game, op_for_kind(kind, SWAP));
	write_op(game, op_for_kind(inverse_kind(kind), PUSH));
	return (1);
}

static void	_qsort_partition(t_game *game, t_kind kind, t_part *parent)
{
	size_t		i;
	t_part		child[STACK_KIND_N];

	if (_end(game, kind, parent) || _simple3(game, kind, parent))
		return ;
#ifdef __DEBUG
	if (game->opt_visual)
	{
		__depth++;
		visualize(__format("Partition Created. at %c [ %d ] ( %d, %d )", 'A' + (kind == OF_STACK_B), __depth, parent->start, parent->length), game);
//		getchar_safe();
	}
#endif
	_half_part(parent, child);
	if (!_smart4(game, kind, parent, child))
	{
		i = parent->length;
		while (i-- > 0)
		{
			if (parent->reverse)
				write_op(game, op_for_kind(kind, REVERSE | ROTATE));
			if (_contains_part(&child[inverse_kind(kind)], game->stack[kind]->rank))
				write_op(game, op_for_kind(inverse_kind(kind), PUSH));
			else if (!parent->reverse)
				write_op(game, op_for_kind(kind, ROTATE));
		}
		if (!parent->reverse)
			child[kind].reverse = game->count[kind] != child[kind].length;
	}
	_qsort_partition(game, OF_STACK_A, &child[OF_STACK_A]);
	_qsort_partition(game, OF_STACK_B, &child[OF_STACK_B]);
#ifdef __DEBUG
	if (game->opt_visual)
	{
		visualize(__format("Partition Removed. at %c [ %d ] ( %d(%d | %d), %d(%d | %d) )", 'A' + (kind == OF_STACK_B), __depth, parent->start, child[0].start, child[1].start, parent->length, child[0].length, child[1].length), game);
//		getchar_safe();
		__depth--;
	}
#endif
}

void	solve_qsort(t_game *game)
{
	t_part	root;

	root.start = 0;
	root.length = game->length;
	root.reverse = 0;
	_qsort_partition(game, OF_STACK_A, &root);
}
