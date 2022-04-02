/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:25:02 by jkong             #+#    #+#             */
/*   Updated: 2022/04/03 03:10:46 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	_apply_swap(t_game *game, t_kind kind)
{
	t_elem	*first;
	t_elem	*second;
	t_elem	*tail;
	t_elem	*next;

	if (game->count[kind] < 2)
		return ;
	first = game->stack[kind];
	second = first->next;
	tail = first->prev;
	next = second->next;
	game->stack[kind] = second;
	if (tail != second)
	{
		tail->next = second;
		second->prev = tail;
	}
	second->next = first;
	first->prev = second;
	if (next != first)
	{
		first->next = next;
		next->prev = first;
	}
}

static t_elem	*_apply_pop(t_game *game, t_kind kind)
{
	t_elem	*result;

	if (game->count[kind] < 1)
		return (NULL);
	result = game->stack[kind];
	if (game->count[kind] > 1)
	{
		game->stack[kind] = result->next;
		result->prev->next = result->next;
		result->next->prev = result->prev;
	}
	else
		game->stack[kind] = NULL;
	game->count[kind]--;
	result->prev = NULL;
	result->next = NULL;
	return (result);
}

static void	_apply_push(t_game *game, t_kind kind, t_elem *elem)
{
	t_elem	**head;

	if (!elem)
		return ;
	head = &game->stack[kind];
	if (*head)
	{
		(*head)->prev->next = elem;
		elem->prev = (*head)->prev;
		(*head)->prev = elem;
		elem->next = *head;
	}
	else
	{
		elem->prev = elem;
		elem->next = elem;
	}
	*head = elem;
	game->count[kind]++;
}

static void	_apply_rotate(t_game *game, t_kind kind, int reverse)
{
	t_elem	*temp;

	if (game->count[kind] < 2)
		return ;
	if (!reverse)
		temp = game->stack[kind]->next;
	else
		temp = game->stack[kind]->prev;
	game->stack[kind] = temp;
}

void	apply_op(t_game *game, t_operation op)
{
	if (op & SWAP)
	{
		if (op & FOR_A)
			_apply_swap(game, OF_STACK_A);
		if (op & FOR_B)
			_apply_swap(game, OF_STACK_B);
	}
	if (op & PUSH)
	{
		if (op & FOR_A)
			_apply_push(game, OF_STACK_A, _apply_pop(game, OF_STACK_B));
		if (op & FOR_B)
			_apply_push(game, OF_STACK_B, _apply_pop(game, OF_STACK_A));
	}
	if (op & ROTATE)
	{
		if (op & FOR_A)
			_apply_rotate(game, OF_STACK_A, op & REVERSE);
		if (op & FOR_B)
			_apply_rotate(game, OF_STACK_B, op & REVERSE);
	}
}
