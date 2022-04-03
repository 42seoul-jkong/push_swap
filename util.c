/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 02:20:43 by jkong             #+#    #+#             */
/*   Updated: 2022/04/04 02:02:13 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_game *game, t_kind kind, t_part *part)
{
	const int		rev = kind == OF_STACK_B;
	t_elem			*elem;
	unsigned int	r;
	size_t			i;

	elem = game->stack[kind];
	if (part->reverse)
		elem = elem->prev;
	r = part->start + ((part->reverse ^ rev) * (part->length - 1));
	i = part->length;
	while (i-- > 0)
	{
		if (elem->rank != r)
			return (0);
		r += 1 - ((part->reverse ^ rev) << 1);
		if (!part->reverse)
			elem = elem->next;
		else
			elem = elem->prev;
	}
	return (1);
}

t_operation	op_for_kind(t_kind kind, t_operation op)
{
	if (kind == OF_STACK_A)
		op |= FOR_A;
	if (kind == OF_STACK_B)
		op |= FOR_B;
	return (op);
}

t_kind	inverse_kind(t_kind kind)
{
	if (kind == OF_STACK_A)
		return (OF_STACK_B);
	if (kind == OF_STACK_B)
		return (OF_STACK_A);
	return (kind ^ 1);
}
