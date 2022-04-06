/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:54 by jkong             #+#    #+#             */
/*   Updated: 2022/04/05 21:14:05 by jkong            ###   ########.fr       */
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
			game->opt_debug = 1;
			i++;
		}
		else if (ft_strcmp(argv[i], "--v") == 0)
		{
			game->opt_visual = 1;
			i++;
		}
		else
			break ;
	}
	return (i);
}

int	main(int argc, char *argv[])
{
	t_game	game;
	int		exit_status;
	int		start;
	int		i;

	ft_memset(&game, 0, sizeof(game));
	start = _process_option(&game, argc, argv);
	i = start;
	while (i < argc)
		game.length += ft_split_count(argv[i++], " ");
	if (game.length == 0)
		return (EXIT_SUCCESS);
	game.table = calloc_safe(game.length, sizeof(*game.table));
	if (!game_fill(game.table, argc, argv, start) || !game_assign(&game))
		exit_error();
	game_link(&game);
	exit_status = app_run(&game);
	game_free(&game);
	return (exit_status);
}
