/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:52 by jkong             #+#    #+#             */
/*   Updated: 2022/04/02 19:31:09 by jkong            ###   ########.fr       */
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
	size_t		i;
	t_part		child[STACK_TYPE_N];

	if (parent->length <= 2 || (parent->length == 3 && game->count[type] == 3))
	{
		if (parent->reverse)
			for (size_t k = 0; k < parent->length; k++)
				write_op(game, _for_type(type, REVERSE | ROTATE));
		if (parent->length == 3)
			do_game_3(game, type);
		else
			do_game_2(game, type);
		if (type == OF_STACK_B)
			for (size_t k = 0; k < parent->length; k++)
				write_op(game, PA);
		return ;
	}
	if (game->opt_visual)
	{
		__depth++;
		visualize(__format("Partition Created. at %c [ %d ] ( %d, %d )", 'A' + (type == OF_STACK_B), __depth, parent->start, parent->length), game);
		getchar_safe();
	}
	child[OF_STACK_B].start = parent->start;
	child[OF_STACK_B].length = parent->length / 2;
	child[OF_STACK_B].reverse = 0;
	child[OF_STACK_A].start = parent->start + child[OF_STACK_B].length;
	child[OF_STACK_A].length = parent->length - child[OF_STACK_B].length;
	child[OF_STACK_A].reverse = 0;
	i = parent->length;
	while (i-- > 0)
	{
		if (parent->reverse)
			write_op(game, _for_type(type, REVERSE | ROTATE));
		if (child[_inverse(type)].start <= game->stack[type]->rank && game->stack[type]->rank < child[_inverse(type)].start + child[_inverse(type)].length)
			write_op(game, _for_type(_inverse(type), PUSH));
		else if (!parent->reverse)
			write_op(game, _for_type(type, ROTATE));
	}
	child[type].reverse = !parent->reverse && game->count[type] != child[type].length;
	_partition(game, OF_STACK_A, &child[OF_STACK_A]);
	_partition(game, OF_STACK_B, &child[OF_STACK_B]);
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
	root.reverse = 0;
	_partition(game, OF_STACK_A, &root);
	if (game->opt_visual)
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
