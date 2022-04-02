/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:52 by jkong             #+#    #+#             */
/*   Updated: 2022/04/02 17:04:10 by jkong            ###   ########.fr       */
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
 */

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

static void	_partition(t_game *game, t_stack_type type, int level)
{
	size_t		i;
	size_t		pop;

	if (game->opt_visual)
	{
		visualize(__format("Partition Created. at %c [ %d ]", 'A' + (type == OF_STACK_B), level), game);
		getchar_safe();
	}
	i = game->count[type];
	pop = 0;
	while (i-- > 0)
	{
		if ((game->stack[type]->rank >> level) & 1)
			write_op(game, _for_type(type, ROTATE));
		else
		{
			write_op(game, _for_type(_inverse(type), PUSH));
			pop++;
		}
	}
	i = pop;
	while (i-- > 0)
		write_op(game, _for_type(type, PUSH));
	if (game->opt_visual)
	{
		visualize(__format("Partition Removed. at %c [ %d ]", 'A' + (type == OF_STACK_B), level), game);
		getchar_safe();
	}
}

void	do_game(t_game *game)
{
	int i;

	if (is_sorted_stack_a(game) || do_game_mini(game))
		return ;
	i = 0;
	while (game->length >> i)
		_partition(game, OF_STACK_A, i++);
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
