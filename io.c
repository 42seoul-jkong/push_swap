/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:25:54 by jkong             #+#    #+#             */
/*   Updated: 2022/03/30 22:26:15 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	getchar_safe(void)
{
	char	c;
	ssize_t	res;

	res = read(STDIN_FILENO, &c, sizeof(c));
	if (res < 0)
		exit(EXIT_FAILURE);
	if (res == 0)
		return (-1);
	return ((unsigned char)c);
}

void	putchar_safe(char c)
{
	ssize_t	r;
	ssize_t	res;

	res = 0;
	while (res == 0)
	{
		r = write(STDOUT_FILENO, &c, sizeof(c));
		if (r < 0)
			exit(EXIT_FAILURE);
		res += r;
	}
}
