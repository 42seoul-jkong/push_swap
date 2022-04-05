/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:54 by jkong             #+#    #+#             */
/*   Updated: 2022/04/05 21:12:46 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	app_run(t_game *game)
{
	if (game->opt_debug)
		run_solver(game);
	else
		return (run_checker(game));
	return (EXIT_SUCCESS);
}
