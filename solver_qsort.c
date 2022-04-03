/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_qsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:42:57 by jkong             #+#    #+#             */
/*   Updated: 2022/04/03 17:51:31 by jkong            ###   ########.fr       */
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

static void	_qsort_partition(t_game *game, t_kind kind, t_part *parent)
{
	size_t		i;
	t_part		child[STACK_KIND_N];

	if (_end(game, kind, parent))
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
