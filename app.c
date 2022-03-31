/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:54 by jkong             #+#    #+#             */
/*   Updated: 2022/04/01 00:31:08 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	_process_option(t_game *game, int argc, char *argv[])
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

static int	_fill(t_elem *table, int argc, char *argv[])
{
	int		i;
	char	**split;
	char	**str_table;
	int		res_atoi;

	i = _process_option(NULL, argc, argv);
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

static int	_assign(t_game *game)
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

static void	_link(t_game *game)
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

int	main(int argc, char *argv[])
{
	t_game	game;
	int		exit_status;
	int		i;

	ft_memset(&game, 0, sizeof(game));
	i = _process_option(&game, argc, argv);
	while (i < argc)
		game.length += ft_split_count(argv[i++], " ");
	game.table = ft_calloc(game.length, sizeof(t_elem));
	if (game.table && _fill(game.table, argc, argv) && _assign(&game))
	{
		_link(&game);
		exit_status = EXIT_SUCCESS;
		if (game.opt_debug)
			exit_status = run_checker(&game);
		else
			do_game(&game);
	}
	else
	{
		write(STDERR_FILENO, "Error\n", 6);
		exit_status = EXIT_FAILURE;
	}
	free(game.table);
	return (exit_status);
}
