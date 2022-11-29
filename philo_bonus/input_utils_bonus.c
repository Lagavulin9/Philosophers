/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:32:49 by jinholee          #+#    #+#             */
/*   Updated: 2022/11/28 15:12:37 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	is_positive_integer(char *str)
{
	int		flag;
	long	num;

	num = 0;
	flag = 0;
	if (*str == '-' || *str == '+' || *str == '0')
	{
		if (*str == '-' || *str == '0')
			return (0);
		str++;
	}
	while (*str)
	{
		if (*str < '0' || '9' < *str)
			return (0);
		flag = 1;
		num = num * 10 + (*str++ - '0');
		if (num > 2147483647)
			return (0);
	}
	return (flag);
}

int	is_valid_input(int argc, char *argv[])
{
	int	i;

	if (argc != 5 && argc != 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (!is_positive_integer(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	res;

	sign = 1;
	while (*str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	res = 0;
	while ('0' <= *str && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return ((int)(sign * res));
}

void	*ft_calloc(size_t size)
{
	unsigned char	*mem;
	size_t			i;

	mem = malloc(size);
	if (mem)
	{
		i = 0;
		while (i < size)
			mem[i++] = 0;
	}
	return ((void *)mem);
}
