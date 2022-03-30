/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:19:05 by jkong             #+#    #+#             */
/*   Updated: 2022/03/31 02:41:47 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_operation	_find_op(char str[5])
{
	if (ft_strcmp(str, "sa") == 0)
		return (SA);
	else if (ft_strcmp(str, "sb") == 0)
		return (SB);
	else if (ft_strcmp(str, "ss") == 0)
		return (SS);
	else if (ft_strcmp(str, "pa") == 0)
		return (PA);
	else if (ft_strcmp(str, "pb") == 0)
		return (PB);
	else if (ft_strcmp(str, "ra") == 0)
		return (RA);
	else if (ft_strcmp(str, "rb") == 0)
		return (RB);
	else if (ft_strcmp(str, "rr") == 0)
		return (RR);
	else if (ft_strcmp(str, "rra") == 0)
		return (RRA);
	else if (ft_strcmp(str, "rrb") == 0)
		return (RRB);
	else if (ft_strcmp(str, "rrr") == 0)
		return (RRR);
	else if (ft_strcmp(str, "") == 0)
		return (NOP);
	return (NONE);
}

static t_operation	_read_op(void)
{
	char		str[5];
	int			i;
	const int	count = sizeof(str) / sizeof(*str);

	i = 0;
	while (i < count)
	{
		str[i] = getchar_safe();
		if (str[i] < 0 || str[i] == '\n')
			break ;
		i++;
	}
	if (i == count)
		return (NONE);
	str[i] = '\0';
	return (_find_op(str));
}

static t_gerr	_check(t_game *game, t_operation latest_op)
{
	unsigned int	i;
	t_elem			*elem;

	if (latest_op == NONE)
		return (GAME_FAILURE_UNDEFINED_OPERATION);
	if (game->count[OF_STACK_B] != 0)
		return (GAME_FAILURE_B_COUNT);
	if (game->count[OF_STACK_A] != game->length)
		return (GAME_FAILURE_A_COUNT);
	elem = game->stack[OF_STACK_A];
	i = 0;
	while (i < game->length)
	{
		if (elem->rank != i)
			return (GAME_FAILURE_SORT);
		elem = elem->next;
		i++;
	}
	if (game->stack[OF_STACK_A] != elem)
		return (GAME_FAILURE_UNKNOWN);
	if (game->stack[OF_STACK_B] != NULL)
		return (GAME_FAILURE_UNKNOWN);
	return (GAME_SUCCESS);
}

int	run_checker(t_game *game)
{
	t_operation	op;
	t_gerr		err;

	op = NONE;
	while (op)
	{
		op = _read_op();
		if (op == NONE || op == NOP)
			break ;
		game->instruction_size++;
		apply_op(game, op);
		if (game->opt_visual)
			visualize("run_checker", game);
	}
	err = _check(game, op);
	if (err != GAME_SUCCESS)
	{
		putstr_safe("KO\n");
		if (game->opt_debug)
			visualize_gerr("run_checker", err);
		return (0);
	}
	putstr_safe("OK\n");
	return (1);
}
