/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:52 by jkong             #+#    #+#             */
/*   Updated: 2022/04/03 18:33:00 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	game_link(t_game *game)
{
	size_t	i;

	if (game->length > 0)
	{
		i = 0;
		while (i < game->length - 1)
		{
			game->table[i].next = &game->table[i + 1];
			game->table[i + 1].prev = &game->table[i];
			i++;
		}
		game->table[i].next = &game->table[0];
		game->table[0].prev = &game->table[i];
	}
	game->stack[OF_STACK_A] = &game->table[0];
	game->count[OF_STACK_A] = game->length;
	game->stack[OF_STACK_B] = NULL;
	game->count[OF_STACK_B] = 0;
	if (game->opt_visual)
		visualize("_link", game);
}

static t_elem	*_table_duplicate(t_elem *table, size_t length)
{
	t_elem	*result;

	if (!table)
		return (NULL);
	result = calloc_safe(length, sizeof(*result));
	ft_memcpy(result, table, length * sizeof(t_elem));
	return (result);
}

t_game	*game_copy(t_game *dest, t_game *src)
{
	ft_memset(dest, 0, sizeof(*dest));
	dest->length = src->length;
	dest->table = _table_duplicate(src->table, src->length);
	game_link(dest);
	dest->opt_debug = src->opt_debug;
	dest->opt_visual = src->opt_visual;
	return (dest);
}

void	game_free(t_game *game)
{
	free(game->table);
	free(game->op_vector);
}
