/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:52 by jkong             #+#    #+#             */
/*   Updated: 2022/04/01 03:43:15 by jkong            ###   ########.fr       */
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

static void	_partition(t_game *game, t_stack_type type, size_t size, size_t lim)
{
	size_t	i;
	size_t	push;
	size_t	rotate;

			char dest[4096];
	if (size <= 2)
	{
		visualize(__format(dest, "TEST %d %d %c", size, lim, 'a' + (type == OF_STACK_B)), game);
		return ;
	}
	i = 0;
	push = 0;
	rotate = 0;
	while (i < size)
	{
		if (game->stack[type]->rank < lim)
		{
			write_op(game, _for_type(_inverse(type), PUSH));
			push++;
		}
		else
		{
			write_op(game, _for_type(type, ROTATE));
			rotate++;
		}
		i++;
	}
	i = 0;
	while (i < rotate)
	{
		write_op(game, _for_type(type, REVERSE | ROTATE));
		i++;
	}
			visualize(__format(dest, "test %d %d %c %d %d", size, lim, 'a' + (type == OF_STACK_B), push, rotate), game);
	_partition(game, _inverse(type), push, lim - lim / 2);
	_partition(game, type, rotate, lim + lim / 2);
}

void	do_game(t_game *game)
{
	if (is_sorted_stack_a(game) || do_game_mini(game))
		return ;
	_partition(game, OF_STACK_A, game->length, game->length / 2);
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
