/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:52 by jkong             #+#    #+#             */
/*   Updated: 2022/04/01 21:03:54 by jkong            ###   ########.fr       */
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

static void	_partition(t_game *game, t_stack_type type, t_part *parent, int depth)
{
	const int	rev = type == OF_STACK_B;
	t_part		first;
	t_part		second;
	size_t		i;
	size_t		rotate;

			visualize(__format("Partition Created. at %c [ %d ] ( %d, %d )", 'A' + (type == OF_STACK_B), depth, parent->start, parent->length), game);
			getchar_safe();
	i = 0;
	rotate = 0;
	while (i < parent->length)
	{
		if ((game->stack[type]->rank < parent->start + parent->length / 2) ^ rev)
			write_op(game, _for_type(_inverse(type), PUSH));
		else
		{
			write_op(game, _for_type(type, ROTATE));
			rotate++;
		}
		i++;
	}
	i = rotate;
	while (i-- > 0)
		write_op(game, _for_type(type, REVERSE | ROTATE));
	second.length = rotate;
	first.length = parent->length - second.length;
	second.start = parent->start + !rev * (first.length + 1);
	first.start = parent->start + rev * (first.length + 1);
	rotate = 0;
	if (first.length > 2)
		_partition(game, _inverse(type), &first, depth + 1);
	else
	{
		_do_game_2(game, _inverse(type));
		i = first.length;
		while (i-- > 0)
			write_op(game, _for_type(type, PUSH));
		rotate += first.length;
	}
	if (second.length > 2)
		_partition(game, type, &second, depth + 1);
	else
	{
		_do_game_2(game, type);
		rotate += second.length;
	}
	i = rotate;
	while (i-- > 0)
		write_op(game, _for_type(type, ROTATE));
}

void	do_game(t_game *game)
{
	t_part	root;

	if (is_sorted_stack_a(game) || do_game_mini(game))
		return ;
	root.start = 0;
	root.length = game->length;
	_partition(game, OF_STACK_A, &root, 0);
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
