/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:25:54 by jkong             #+#    #+#             */
/*   Updated: 2022/04/03 18:33:40 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	read_safe(int fd, void *buf, size_t len)
{
	size_t	off;
	ssize_t	res;

	off = 0;
	while (off < len)
	{
		res = read(fd, buf + off, len - off);
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

	if (!read_safe(STDIN_FILENO, &c, sizeof(c)))
		return (-1);
	return ((unsigned char)c);
}

void	write_safe(int fd, const void *buf, size_t len)
{
	size_t	off;
	ssize_t	res;

	off = 0;
	while (off < len)
	{
		res = write(fd, buf + off, len - off);
		if (res < 0)
			exit(EXIT_FAILURE);
		off += res;
	}
}

void	putchar_safe(char c)
{
	write_safe(STDOUT_FILENO, &c, sizeof(c));
}

void	putstr_safe(const char *str)
{
	write_safe(STDOUT_FILENO, str, ft_strlen(str));
}
