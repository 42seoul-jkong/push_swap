/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:19:05 by jkong             #+#    #+#             */
/*   Updated: 2022/04/06 01:42:02 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_operation	_find_op(char str[BUFFER_SIZE])
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
	return (NONE);
}

static t_operation	_read_op(void)
{
	char		str[BUFFER_SIZE];
	const int	count = sizeof(str) / sizeof(*str);
	int			i;
	int			input;
	t_operation	op;

	i = 0;
	input = -1;
	while (i < count - 1)
	{
		input = getchar_safe();
		if (input < 0 || input == '\n')
			break ;
		str[i++] = input;
	}
	if (i == 0 && input < 0)
		return (NOP);
	str[i] = '\0';
	op = _find_op(str);
	if (op == NONE)
	{
		while (input >= 0 && input != '\n')
			input = getchar_safe();
	}
	return (op);
}

int	is_sort_completed(t_game *game)
{
	t_part	all;

	all.start = 0;
	all.length = game->length;
	all.reverse = 0;
	return (is_sorted(game, OF_STACK_A, &all));
}

static t_gerror	_check(t_game *game)
{
	if (game->count[OF_STACK_B] != 0)
		return (GAME_FAILURE_B_COUNT);
	if (game->count[OF_STACK_A] != game->length)
		return (GAME_FAILURE_A_COUNT);
	if (!game->stack[OF_STACK_A])
		return (GAME_FAILURE_UNKNOWN);
	if (!is_sort_completed(game))
		return (GAME_FAILURE_SORT);
	return (GAME_SUCCESS);
}

int	run_checker(t_game *game)
{
	t_operation	op;
	t_gerror	err;

	op = NONE;
	while (op != NOP)
	{
		op = _read_op();
		if (op == NONE)
			exit_error();
		game->op_size++;
		apply_op(game, op);
		if (game->opt_visual)
			visualize("run_checker", game);
	}
	err = _check(game);
	if (err != GAME_SUCCESS)
	{
		putstr_safe("KO\n");
		if (game->opt_debug)
			visualize_gerror("run_checker", err);
		return (EXIT_KO);
	}
	putstr_safe("OK\n");
	return (EXIT_SUCCESS);
}
