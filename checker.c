/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:19:05 by jkong             #+#    #+#             */
/*   Updated: 2022/03/30 22:26:37 by jkong            ###   ########.fr       */
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
	return (NOP);
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
		return (NOP);
	str[i] = '\0';
	return (_find_op(str));
}

int	run_checker(t_game *game)
{
	t_operation	op;

	op = NONE;
	while (op)
	{
		op = _read_op();
		apply_op(game, op);
	}
	return (check(game) == GAME_SUCCESS);
}

t_gerr	check(t_game *game)
{
	unsigned int	i;
	t_elem			*elem;

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
	}
	if (game->stack[OF_STACK_A] != elem)
		return (GAME_FAILURE_UNKNOWN);
	if (game->stack[OF_STACK_B] != NULL)
		return (GAME_FAILURE_UNKNOWN);
	return (GAME_SUCCESS);
}
