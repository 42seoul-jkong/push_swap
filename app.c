/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:54 by jkong             #+#    #+#             */
/*   Updated: 2022/03/29 16:23:57 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	on_exit(t_game *game, int number)
{
	if (number == 1)
		write(STDERR_FILENO, "Error\n", 6);
	free(game->table);
	return (number);
}

static int	process_option(t_game *game, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (argc > i)
	{
		if (ft_strcmp(argv[i], "--d") == 0)
		{
			if (game)
				game->opt_debug = 1;
			i++;
		}
		else if (ft_strcmp(argv[i], "--v") == 0)
		{
			if (game)
				game->opt_visual = 1;
			i++;
		}
		else
			break ;
	}
	return (i);
}

static int	fill(t_elem *table, int argc, char *argv[])
{
	int		i;
	char	**split;
	char	**str_table;
	int		res_atoi;

	i = process_option(NULL, argc, argv);
	while (i > 0 && i < argc)
	{
		split = ft_split(argv[i++], " ");
		if (split)
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

static int	unique(t_game *game)
{
	size_t			i;
	size_t			j;

	i = 0;
	while (i < game->count)
	{
		j = 0;
		while (j < i)
		{
			if (game->table[i].number == game->table[j].number)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_game	game;
	int		i;

	ft_memset(&game, 0, sizeof(game));
	i = process_option(&game, argc, argv);
	while (i < argc)
		game.count += ft_split_count(argv[i++], " ");
	game.table = ft_calloc(game.count, sizeof(t_elem));
	if (!game.table || !fill(game.table, argc, argv) || !unique(&game))
		return (on_exit(&game, 1));
	do_game(&game);
	return (on_exit(&game, 0));
}
