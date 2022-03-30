/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:52 by jkong             #+#    #+#             */
/*   Updated: 2022/03/30 21:11:28 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_elem	*_link_table(t_elem *table, size_t length)
{
	size_t	i;

	if (length > 0)
	{
		table[0].prev = &table[length - 1];
		i = 0;
		while (i < length - 1)
		{
			table[i].next = &table[i + 1];
			table[i + 1].prev = &table[i];
			i++;
		}
		table[length - 1].next = &table[0];
	}
	return (&table[0]);
}

#include <stdio.h>

static void	___visualize(const char *title, t_game *game)
{
	printf("[ %s ]\n", title);
	t_elem *e;
	printf("\ta:");
	e = game->stack[OF_STACK_A];
	for (size_t i = 0; i < game->count[OF_STACK_A]; i++)
	{
		printf(" %d", e->number);
		e = e->next;
	}
	printf("\n");
	printf("\tb: ");
	e = game->stack[OF_STACK_B];
	for (size_t i = 0; i < game->count[OF_STACK_B]; i++)
	{
		printf(" %d", e->number);
		e = e->next;
	}
	printf("\n");
	printf("\n");
}

static void	___test_game(t_game *game)
{
	unsigned int	i;

	___visualize("FIRST", game);
	if (game->count[OF_STACK_A] >= 2)
	{
		i = game->stack[OF_STACK_A]->next->rank;
		if (game->stack[OF_STACK_A]->rank > i)
			do_op(game, SA);
	}
	___visualize("SECOND", game);
	i = 0;
	while (i < game->length)
	{
		if (game->stack[OF_STACK_A]->rank < game->length / 2)
			do_op(game, PB);
		else
			do_op(game, RA);
		i++;
	}
	___visualize("THIRD", game);
	if (game->count[OF_STACK_A] >= 2)
	{
		i = game->stack[OF_STACK_A]->next->rank;
		if (game->stack[OF_STACK_A]->rank > i)
			do_op(game, SA);
	}
	if (game->count[OF_STACK_B] >= 2)
	{
		i = game->stack[OF_STACK_B]->next->rank;
		if (game->stack[OF_STACK_B]->rank > i)
			do_op(game, SB);
	}
	___visualize("FOURTH", game);
}

void	do_game(t_game *game)
{
	game->stack[OF_STACK_A] = _link_table(game->table, game->length);
	game->count[OF_STACK_A] = game->length;
	game->stack[OF_STACK_B] = NULL;
	game->count[OF_STACK_B] = 0;
	___test_game(game);
}

void	do_op(t_game *game, t_operation op)
{
	char	c;

	apply_op(game, op);
	if (op & REVERSE)
		write(STDOUT_FILENO, "r", 1);
	if (op & SWAP)
		c = 's';
	else if (op & PUSH)
		c = 'p';
	else if (op & ROTATE)
		c = 'r';
	write(STDOUT_FILENO, &c, 1);
	if ((op & FOR_A) && (op & FOR_B))
		write(STDOUT_FILENO, &c, 1);
	else if (op & FOR_A)
		write(STDOUT_FILENO, "a", 1);
	else if (op & FOR_B)
		write(STDOUT_FILENO, "b", 1);
	write(STDOUT_FILENO, "\n", 1);
}
