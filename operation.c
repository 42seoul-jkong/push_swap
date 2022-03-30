/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:25:02 by jkong             #+#    #+#             */
/*   Updated: 2022/03/30 19:18:05 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	_do_swap(t_game *game, t_stack_type type)
{
	t_elem	*first;
	t_elem	*second;

	if (game->count[type] < 2)
		return ;
	first = game->stack[type];
	second = first->next;
	game->stack[type] = second;
	second->prev = first->prev;
	first->next = second->next;
	second->next = first;
	first->prev = second;
}

static t_elem	*_do_pop(t_game *game, t_stack_type type)
{
	t_elem	*result;

	if (game->count[type] < 1)
		return (NULL);
	result = game->stack[type];
	if (game->count[type] > 1)
	{
		game->stack[type] = result->next;
		result->prev->next = result->next;
		result->next->prev = result->prev;
	}
	else
		game->stack[type] = NULL;
	game->count[type]--;
	result->prev = result;
	result->next = result;
	return (result);
}

static void	_do_push(t_game *game, t_stack_type type, t_elem *elem)
{
	t_elem	**head;

	if (!elem)
		return ;
	head = &game->stack[type];
	if (*head)
	{
		(*head)->prev->next = elem;
		elem->prev = (*head)->prev;
		(*head)->prev = elem;
		elem->next = *head;
	}
	*head = elem;
	game->count[type]++;
}

static void	_do_rotate(t_game *game, t_stack_type type, int reverse)
{
	t_elem	*temp;

	if (game->count[type] < 2)
		return ;
	if (!reverse)
		temp = game->stack[type]->next;
	else
		temp = game->stack[type]->prev;
	game->stack[type] = temp;
}

void	do_op(t_game *game, t_operation op)
{
	if (op & SWAP)
	{
		if (op & FOR_A)
			_do_swap(game, OF_STACK_A);
		if (op & FOR_B)
			_do_swap(game, OF_STACK_B);
	}
	if (op & PUSH)
	{
		if (op & FOR_A)
			_do_push(game, OF_STACK_A, _do_pop(game, OF_STACK_B));
		if (op & FOR_B)
			_do_push(game, OF_STACK_B, _do_pop(game, OF_STACK_A));
	}
	if (op & ROTATE)
	{
		if (op & FOR_A)
			_do_rotate(game, OF_STACK_A, op & REVERSE);
		if (op & FOR_B)
			_do_rotate(game, OF_STACK_B, op & REVERSE);
	}
}
