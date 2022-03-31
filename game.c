/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:52 by jkong             #+#    #+#             */
/*   Updated: 2022/04/01 04:08:00 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stack_type	_inverse(t_stack_type type)
{
	return (type ^ 1);
}

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

		static char *__format(char dest[4096], char *format, ...)
		{
			va_list va;
			va_start(va, format);
			vsprintf(dest, format, va);
			va_end(va);
			return dest;
		}

static void	_partition(t_game *game, t_stack_type type, t_part *parent)
{
	t_part	first;
	t_part	second;
	size_t	i;

			char dest[4096];
	if (parent->length <= 2)
	{
		visualize(__format(dest, "TEST %d %d %c", parent->start, parent->length, 'a' + (type == OF_STACK_B)), game);
		return ;
	}
	i = 0;
	while (i < parent->length)
	{
		if (game->stack[type]->rank < parent->start + parent->length / 2)
			write_op(game, _for_type(_inverse(type), PUSH));
		else
			write_op(game, _for_type(type, ROTATE));
		i++;
	}
			visualize(__format(dest, "test %d %d %c %d", parent->start, parent->length, 'a' + (type == OF_STACK_B), rotate), game);
	first.start = parent->start;
	first.length = parent->length - parent->length / 2;
	_partition(game, _inverse(type), &first);
	second.start = parent->start + parent->length / 2;
	second.length = parent->length / 2;
	_partition(game, type, &second);
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
