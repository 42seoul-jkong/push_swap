/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:52 by jkong             #+#    #+#             */
/*   Updated: 2022/03/30 03:30:01 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	link_table(t_elem *table, size_t count)
{
	size_t	i;

	if (count > 0)
	{
		table[0].prev = &table[count - 1];
		i = 0;
		while (i < count - 1)
		{
			table[i].next = &table[i + 1];
			table[i + 1].prev = &table[i];
			i++;
		}
		table[count - 1].next = &table[0];
	}
}

void	ready_game(t_game *game)
{
	link_table(game->table, game->count);
}

void	do_game(t_game *game)
{
	(void)game;
}
