/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:42:17 by jkong             #+#    #+#             */
/*   Updated: 2022/04/06 02:30:10 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>

# define BUFFER_SIZE 4
# define VECTOR_SIZE 1024
# define EXIT_KO 2

typedef enum e_kind
{
	OF_STACK_A,
	OF_STACK_B,
	STACK_KIND_N
}	t_kind;

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

typedef enum e_gerror
{
	GAME_SUCCESS,
	GAME_FAILURE_SORT,
	GAME_FAILURE_A_COUNT,
	GAME_FAILURE_B_COUNT,
	GAME_FAILURE_UNKNOWN = -1,
}	t_gerror;

typedef struct s_elem
{
	int				number;
	unsigned int	rank;
	struct s_elem	*prev;
	struct s_elem	*next;
}	t_elem;

typedef struct s_game
{
	size_t		length;
	t_elem		*table;
	size_t		count[STACK_KIND_N];
	t_elem		*stack[STACK_KIND_N];
	size_t		op_size;
	size_t		op_capacity;
	t_operation	*op_vector;
	size_t		op_optimize;
	int			opt_debug;
	int			opt_visual;
}	t_game;

typedef struct s_part
{
	unsigned int	start;
	size_t			length;
	int				reverse;
}	t_part;

/*
** app_solver.c | app_checker.c
*/
int			app_run(t_game *game);

/*
** Push Swap Game Management
** game.c
*/
int			game_fill(t_elem *table, int argc, char *argv[], int i);
int			game_assign(t_game *game);
void		game_link(t_game *game);
void		game_free(t_game *game);

/*
** checker.c
*/
int			run_checker(t_game *game);
int			is_sort_completed(t_game *game);

/*
** solver.c
*/
void		run_solver(t_game *game);
void		write_op(t_game *game, t_operation op);

/*
** solver_micro.c
** solver_mini.c
*/
void		solve_2(t_game *game, t_kind kind);
void		try_swap(t_game *game, t_kind kind);
void		solve_3(t_game *game, t_kind kind);

/*
** solver_qsort.c
*/
void		solve_qsort(t_game *game);

/*
** operation.c
*/
void		apply_op(t_game *game, t_operation op);

/*
** visualize.c
*/
void		visualize(const char *title, t_game *game);
void		visualize_gerror(const char *title, t_gerror err);

/*
** util.c
*/
int			is_sorted(t_game *game, t_kind kind, t_part *part);
t_operation	op_for_kind(t_kind kind, t_operation op);
t_kind		inverse_kind(t_kind kind);
int			contains_part(t_part *part, unsigned int rank);
void		exit_error(void);

/*
** Forty-Two Library Functions
** libft.c
** libft_try_atoi.c
** libft_split.c
*/
size_t		ft_strlen(const char *s);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
void		*ft_calloc(size_t count, size_t size);
int			ft_try_atoi(const char *str, int *out);
size_t		ft_split_count(const char *s, const char *set);
char		**ft_split(const char *s, const char *set);
char		**ft_split_free(char **ptr);

/*
** safe_mem.c
*/
void		*malloc_safe(size_t size);
void		*calloc_safe(size_t count, size_t size);

/*
** safe_io.c
*/
int			read_safe(int fd, void *buf, size_t len);
int			getchar_safe(void);
void		write_safe(int fd, const void *buf, size_t len);
void		putstr_safe(const char *str);
void		puterr_safe(const char *str);

#endif
