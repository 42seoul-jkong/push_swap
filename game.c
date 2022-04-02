/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:52 by jkong             #+#    #+#             */
/*   Updated: 2022/04/02 15:41:16 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stack_type	_inverse(t_stack_type type)
{
	return (type ^ 1);
}

/*
 * Deprecated cause duplicated
 */
static t_operation	_for_type(t_stack_type type, t_operation op)
{
	if (type == OF_STACK_A)
		op |= FOR_A;
	if (type == OF_STACK_B)
		op |= FOR_B;
	return (op);
}

/*
 * Deprecated cause duplicated
 */
static void	_do_game_2(t_game *game, t_stack_type type)
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

		#include <stdio.h>
		#include <stdarg.h>

		static char *__format(char *format, ...)
		{
			static char dest[4096];
			va_list va;
			va_start(va, format);
			vsprintf(dest, format, va);
			va_end(va);
			return dest;
		}

		static int __depth;

static void	_partition(t_game *game, t_stack_type type, t_part *parent)
{
	const int	rev = type == OF_STACK_B;
	t_part		child[STACK_TYPE_N];
	size_t		i;

	if (game->opt_visual)
	{
		__depth++;
		visualize(__format("Partition Created. at %c [ %d ] ( %d, %d )", 'A' + (type == OF_STACK_B), __depth, parent->start, parent->length), game);
		getchar_safe();
	}
	child[0].start = parent->start;
	child[0].length = parent->length / 2;
	child[1].start = parent->start + child[0].length;
	child[1].length = parent->length - child[0].length;
	i = parent->length;
	while (i-- > 0)
	{
		if (child[0].start <= game->stack[type]->rank && game->stack[type]->rank < child[0].start + child[0].length)
			write_op(game, _for_type(_inverse(type), PUSH));
		else
			write_op(game, _for_type(type, ROTATE));
	}
	i = child[1].length;
	if (i != game->count[type])
	{
		while (i-- > 0)
			write_op(game, _for_type(type, REVERSE | ROTATE));
	}
	int k;
	for (k = 0; k <= 1; k++)
	{
		i = child[k].length;
		if (i > 2)
			_partition(game, type ^ !k, &child[k]);
		else
		{
			if (i >= 2)
				_do_game_2(game, type ^ !k);
			if (rev ^ !k)
			{
				while (i-- > 0)
					write_op(game, PA);
				i = child[k].length;
			}
			while (i-- > 0)
				write_op(game, RA);
		}
	}
	if (game->opt_visual)
	{
		visualize(__format("Partition Removed. at %c [ %d ] ( %d(%d | %d), %d(%d | %d) )", 'A' + (type == OF_STACK_B), __depth, parent->start, child[0].start, child[1].start, parent->length, child[0].length, child[1].length), game);
		getchar_safe();
		__depth--;
	}
}

void	do_game(t_game *game)
{
	t_part	root;

	if (is_sorted_stack_a(game) || do_game_mini(game))
		return ;
	root.start = 0;
	root.length = game->length;
	_partition(game, OF_STACK_A, &root);
	visualize("Not implemented. KO :(", game);
}

void	write_op(t_game *game, t_operation op)
{
	char	c;

	if (op & SWAP)
		c = 's';
	else if (op & PUSH)
		c = 'p';
	else if (op & ROTATE)
		c = 'r';
	else
		return ;
	if (op & REVERSE)
		putchar_safe('r');
	putchar_safe(c);
	if ((op & FOR_A) && (op & FOR_B))
		putchar_safe(c);
	else if (op & FOR_A)
		putchar_safe('a');
	else if (op & FOR_B)
		putchar_safe('b');
	putchar_safe('\n');
	game->instruction_size++;
	apply_op(game, op);
}
