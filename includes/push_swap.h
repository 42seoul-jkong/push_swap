/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:42:17 by jkong             #+#    #+#             */
/*   Updated: 2022/04/01 04:07:22 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define MINI_LIMIT 3

typedef struct s_elem
{
	int				number;
	unsigned int	rank;
	struct s_elem	*prev;
	struct s_elem	*next;
}	t_elem;

typedef enum e_stack_type
{
	OF_STACK_A,
	OF_STACK_B,
	STACK_TYPE_N
}	t_stack_type;

/**
 * To do this you have the following operations at your disposal:
 * 
 * SA : swap a
 * swap the first 2 elements at the top of stack a. Do nothing if there
 * is only one or no elements).
 * 
 * SB : swap b
 * swap the first 2 elements at the top of stack b. Do nothing if there
 * is only one or no elements).
 * 
 * SS : sa and sb at the same time.
 * 
 * PA : push a
 * take the first element at the top of b and put it at the top of a. Do
 * nothing if b is empty.
 * 
 * PB : push b
 * take the first element at the top of a and put it at the top of b. Do
 * nothing if a is empty.
 * 
 * RA : rotate a
 * shift up all elements of stack a by 1. The first element becomes
 * the last one.
 * 
 * RB : rotate b
 * shift up all elements of stack b by 1. The first element becomes
 * the last one.
 * 
 * RR : ra and rb at the same time.
 * 
 * RRA : reverse rotate a
 * shift down all elements of stack a by 1. The last element
 * becomes the first one.
 * 
 * RRB : reverse rotate b
 * shift down all elements of stack b by 1. The last element
 * becomes the first one.
 * 
 * RRR : rra and rrb at the same time.
 */
typedef enum e_operation
{
	NONE = -1,
	NOP = 0,
	FOR_A = 1,
	FOR_B = 2,
	FOR_SAME = FOR_A | FOR_B,
	SWAP = 1 << 2,
	PUSH = 1 << 3,
	ROTATE = 1 << 4,
	REVERSE = 1 << 5,
	SA = SWAP | FOR_A,
	SB = SWAP | FOR_B,
	SS = SWAP | FOR_SAME,
	PA = PUSH | FOR_A,
	PB = PUSH | FOR_B,
	RA = ROTATE | FOR_A,
	RB = ROTATE | FOR_B,
	RR = ROTATE | FOR_SAME,
	RRA = REVERSE | ROTATE | FOR_A,
	RRB = REVERSE | ROTATE | FOR_B,
	RRR = REVERSE | ROTATE | FOR_SAME
}	t_operation;

typedef enum e_gerr
{
	GAME_SUCCESS,
	GAME_FAILURE_SORT,
	GAME_FAILURE_A_COUNT,
	GAME_FAILURE_B_COUNT,
	GAME_FAILURE_UNDEFINED_OPERATION,
	GAME_FAILURE_UNKNOWN = -1,
}	t_gerr;

typedef struct s_game
{
	size_t	length;
	t_elem	*table;
	size_t	count[STACK_TYPE_N];
	t_elem	*stack[STACK_TYPE_N];
	int		instruction_size;
	int		opt_debug;
	int		opt_visual;
}	t_game;

typedef struct s_part
{
	unsigned int	start;
	size_t			length;
}	t_part;

/*
** game.c
*/
void	do_game(t_game *game);
void	write_op(t_game *game, t_operation op);

/*
** game_mini.c
*/
int		do_game_mini(t_game *game);

/*
** checker.c
*/
int		run_checker(t_game *game);

/*
** visualize.c
*/
void	visualize(const char *title, t_game *game);
void	visualize_gerr(const char *title, t_gerr err);

/*
** operation.c
*/
void	apply_op(t_game *game, t_operation op);

/*
** util.c
*/
int		is_sorted_stack_a(t_game *game);

/*
** Forty-Two Library Functions (libft*.c)
*/
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
int		ft_try_atoi(const char *str, int *out);
size_t	ft_split_count(const char *s, const char *set);
char	**ft_split(const char *s, const char *set);
char	**ft_split_free(char **ptr);

/*
** safe_io.c
*/
int		get_safe(void *buf, size_t len);
int		getchar_safe(void);
void	put_safe(const void *buf, size_t len);
void	putchar_safe(char c);
void	putstr_safe(const char *str);

#endif
