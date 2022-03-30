/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:47:09 by jkong             #+#    #+#             */
/*   Updated: 2022/03/31 01:43:49 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	putnbr_int(int n)
{
	const int	sign = n < 0;
	char		buf[11];
	int			i;

	i = sizeof(buf);
	if (!n)
		buf[--i] = '0';
	while (n)
	{
		buf[--i] = '0' + (1 - (sign << 1)) * (n % 10);
		n /= 10;
	}
	if (sign)
		buf[--i] = '-';
	put_safe(buf + i, sizeof(buf) - i);
}

void	visualize(const char *title, t_game *game)
{
	t_elem	*e;
	size_t	i;

	putstr_safe("[ ");
	putstr_safe(title);
	putstr_safe(" ]\n\tA:");
	e = game->stack[OF_STACK_A];
	i = 0;
	while (i++ < game->count[OF_STACK_A])
	{
		putstr_safe(" ");
		putnbr_int(e->number);
		e = e->next;
	}
	putstr_safe("\n\tB:");
	e = game->stack[OF_STACK_B];
	i = 0;
	while (i++ < game->count[OF_STACK_B])
	{
		putstr_safe(" ");
		putnbr_int(e->number);
		e = e->next;
	}
	putstr_safe("\n\n");
}
