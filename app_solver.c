/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:53:54 by jkong             #+#    #+#             */
/*   Updated: 2022/04/05 19:58:12 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	app_run(t_game *game)
{
	if (game->opt_debug)
		return (run_checker(game));
	else
		run_solver(game);
	return (EXIT_SUCCESS);
}
