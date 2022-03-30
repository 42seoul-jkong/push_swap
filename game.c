/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:52 by jkong             #+#    #+#             */
/*   Updated: 2022/03/30 19:18:16 by jkong            ###   ########.fr       */
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

/*
#include <stdio.h>

void	visualize(const char *title, t_game *game)
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
*/

void	do_game(t_game *game)
{
	game->stack[OF_STACK_A] = _link_table(game->table, game->length);
	game->count[OF_STACK_A] = game->length;
	game->stack[OF_STACK_B] = NULL;
	game->count[OF_STACK_B] = 0;
	(void)game;
}
