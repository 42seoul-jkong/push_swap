/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 02:20:43 by jkong             #+#    #+#             */
/*   Updated: 2022/04/01 02:30:12 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted_stack_a(t_game *game)
{
	unsigned int	i;
	t_elem			*elem;

	if (game->count[OF_STACK_A] != game->length)
		return (0);
	elem = game->stack[OF_STACK_A];
	i = 0;
	while (i < game->length)
	{
		if (elem->rank != i)
			return (0);
		i++;
		elem = elem->next;
	}
	return (1);
}
