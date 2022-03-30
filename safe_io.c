/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:25:54 by jkong             #+#    #+#             */
/*   Updated: 2022/03/31 01:03:57 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_safe(void *buf, size_t len)
{
	size_t	off;
	ssize_t	res;

	off = 0;
	while (off < len)
	{
		res = read(STDIN_FILENO, buf + off, len - off);
		if (res < 0)
			exit(EXIT_FAILURE);
		if (res == 0)
			return (0);
		off += res;
	}
	return (1);
}

int	getchar_safe(void)
{
	char	c;

	if (!get_safe(&c, sizeof(c)))
		return (-1);
	return ((unsigned char)c);
}

void	put_safe(const void *buf, size_t len)
{
	size_t	off;
	ssize_t	res;

	off = 0;
	while (off < len)
	{
		res = write(STDOUT_FILENO, buf + off, len - off);
		if (res < 0)
			exit(EXIT_FAILURE);
		off += res;
	}
}

void	putchar_safe(char c)
{
	put_safe(&c, sizeof(c));
}

void	putstr_safe(const char *str)
{
	put_safe(str, ft_strlen(str));
}
