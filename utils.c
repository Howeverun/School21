/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 23:48:19 by marvin            #+#    #+#             */
/*   Updated: 2022/02/01 23:48:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	print_in_fd(int n, int fd, int i, int result[100])
{
	char	a;

	while (n != 0)
	{
		a = n % 10;
		if (a < 0)
			a *= -1;
		result[i] = a;
		n = n / 10;
		i++;
	}
	while (--i >= 0)
	{
		a = result[i] + 48;
		write(fd, &a, 1);
	}
	write(1, "\n", 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		result[100];
	int		i;

	i = 0;
	if (n == 0)
	{
		result[0] = 0;
		i++;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	print_in_fd(n, fd, i, result);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - '0';
		if (res < 0 && sign == 1)
			return (-1);
		if ((res * sign) > 0 && sign == -1)
			return (0);
		i++;
	}
	return (res * sign);
}
