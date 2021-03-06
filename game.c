/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:52 by jkong             #+#    #+#             */
/*   Updated: 2022/04/05 20:56:52 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	game_fill(t_elem *table, int argc, char *argv[], int i)
{
	char	**split;
	char	**str_table;
	int		res_atoi;

	while (i > 0 && i < argc)
	{
		split = ft_split(argv[i++], " ");
		if (split && *split)
		{
			str_table = split;
			while (i > 0 && *str_table)
			{
				if (ft_try_atoi(*str_table++, &res_atoi))
					table++->number = res_atoi;
				else
					i = 0;
			}
		}
		else
			i = 0;
		ft_split_free(split);
	}
	return (i == argc);
}

int	game_assign(t_game *game)
{
	size_t			i;
	size_t			j;
	unsigned int	rank;

	i = 0;
	while (i < game->length)
	{
		rank = 0;
		j = 0;
		while (j < i)
		{
			if (game->table[i].number == game->table[j].number)
				return (0);
			if (game->table[i].number > game->table[j].number)
				rank++;
			else
				game->table[j].rank++;
			j++;
		}
		game->table[i].rank = rank;
		i++;
	}
	return (1);
}

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
}

void	game_free(t_game *game)
{
	free(game->table);
	free(game->op_vector);
}
