/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:47:09 by jkong             #+#    #+#             */
/*   Updated: 2022/04/03 03:39:26 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	_putnbr_int(int n)
{
	const int	sign = n < 0;
	char		buf[11];
	size_t		i;

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

static void	_visualize_stack(t_elem *stack, size_t count)
{
	size_t	i;

	putstr_safe(" (");
	_putnbr_int(count);
	putstr_safe(")");
	i = 0;
	while (i++ < count)
	{
		putstr_safe(" ");
		_putnbr_int(stack->number);
		stack = stack->next;
	}
}

void	visualize(const char *title, t_game *game)
{
	putstr_safe("[ ");
	putstr_safe(title);
	putstr_safe(" ]");
	putstr_safe("\n\tsize of instruction = ");
	_putnbr_int(game->op_size - game->op_optimize);
	if (game->op_optimize)
	{
		putstr_safe(" (");
		_putnbr_int(-game->op_optimize);
		putstr_safe(")");
	}
	putstr_safe(" op(s)");
	putstr_safe("\n\tA:");
	_visualize_stack(game->stack[OF_STACK_A], game->count[OF_STACK_A]);
	putstr_safe("\n\tB:");
	_visualize_stack(game->stack[OF_STACK_B], game->count[OF_STACK_B]);
	putstr_safe("\n\n");
}

void	visualize_gerror(const char *title, t_gerror err)
{
	putstr_safe("! ");
	putstr_safe(title);
	putstr_safe(" !");
	putstr_safe("\n\tGame Error number = ");
	_putnbr_int(err);
	putstr_safe("\n\tMessage: ");
	if (err == GAME_FAILURE_SORT)
		putstr_safe("Not sorted on stack A");
	else if (err == GAME_FAILURE_A_COUNT)
		putstr_safe("All elements not collected at stack A");
	else if (err == GAME_FAILURE_B_COUNT)
		putstr_safe("Any elements was remaining in stack B");
	else if (err == GAME_FAILURE_UNDEFINED_OPERATION)
		putstr_safe("Undefined instruction detected");
	else if (err == GAME_FAILURE_UNKNOWN)
		putstr_safe("Unknown reason");
	putstr_safe("\n\n");
}
