/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 01:02:26 by jkong             #+#    #+#             */
/*   Updated: 2022/03/31 01:08:37 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** DEPRECATED
*/
void	do_game_mini(t_game *game)
{
	unsigned int	i;

	visualize("FIRST", game);
	if (game->count[OF_STACK_A] >= 2)
	{
		i = game->stack[OF_STACK_A]->next->rank;
		if (game->stack[OF_STACK_A]->rank > i)
			write_op(game, SA);
	}
	visualize("SECOND", game);
	i = 0;
	while (i < game->length)
	{
		if (game->stack[OF_STACK_A]->rank < game->length / 2)
			write_op(game, PB);
		else
			write_op(game, RA);
		i++;
	}
	visualize("THIRD", game);
	if (game->count[OF_STACK_A] >= 2)
	{
		i = game->stack[OF_STACK_A]->next->rank;
		if (game->stack[OF_STACK_A]->rank > i)
			write_op(game, SA);
	}
	if (game->count[OF_STACK_B] >= 2)
	{
		i = game->stack[OF_STACK_B]->next->rank;
		if (game->stack[OF_STACK_B]->rank > i)
			write_op(game, SB);
	}
	visualize("FOURTH", game);
}
