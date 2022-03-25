/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_try_atoi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:19:54 by jkong             #+#    #+#             */
/*   Updated: 2022/03/25 14:10:23 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	_isspace(int c)
{
	return ((011 <= c && c <= 015) || c == ' ');
}

static int	_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static long	_atol(const char *str)
{
	int		sign;
	long	number;

	while (_isspace(*str))
		str++;
	sign = 0;
	if (*str == '+' || *str == '-')
		sign = *str++ == '-';
	number = 0;
	while (*str && _isdigit(*str))
		number = 10L * number + (1 - (sign << 1)) * (*str++ - '0');
	return (number);
}

static int	_nbrlen(int n)
{
	const int	radix = 10;
	int			count;

	count = n == 0;
	while (n != 0)
	{
		count++;
		n /= radix;
	}
	return (count);
}

int	ft_try_atoi(const char *str, int *out)
{
	int		i;
	int		j;
	long	number;

	if (!out)
		return (0);
	*out = 0;
	i = *str == '+' || *str == '-';
	while (str[i] == '0')
		i++;
	j = 0;
	while (_isdigit(str[i + j]))
		j++;
	if (j > _nbrlen(INT_MAX) || str[i + j])
		return (0);
	number = _atol(str);
	if (number < INT_MIN || number > INT_MAX)
		return (0);
	*out = number;
	return (1);
}
