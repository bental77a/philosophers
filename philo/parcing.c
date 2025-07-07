/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 07:21:40 by mohben-t          #+#    #+#             */
/*   Updated: 2025/07/04 20:50:51 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_empty_or_whitespace(const char *str)
{
	if (!str || *str == '\0')
		return (1);
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
			return (0);
		str++;
	}
	return (1);
}

int	check_digit(char **str)
{
	int		i;
	char	*s;

	i = 0;
	while (str[i])
	{
		if (is_empty_or_whitespace(str[i]))
			return (0);
		s = str[i];
		while (*s)
		{
			if (*s < '0' || *s > '9')
				return (0);
			s++;
		}
		i++;
	}

	
	return (1);
}

long	ft_atoi(const char *arg)
{
	int		index;
	long	num;

	index = 0;
	num = 0;
	if (arg && arg[index] == '+')
		index++;
	if (!arg || !arg[index])
		return (-1);
	while (arg[index])
	{
		if (!(arg[index] >= '0' && arg[index] <= '9'))
			return (-1);
		num = (arg[index] - 48) + (num * 10);
		if (num < -2147483648 || num > 2147483647)
			return (-1);
		index++;
	}
	return (num);
}

int	valid_args(char **av, int ac)
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;

	if (ac != 5 && ac != 6)
		return (0);
	if (!check_digit(av + 1))
		return (0);
	num_philos = ft_atoi(av[1]);
	time_to_die = ft_atoi(av[2]);
	time_to_eat = ft_atoi(av[3]);
	time_to_sleep = ft_atoi(av[4]);
	if (num_philos <= 0 || num_philos > 200 || time_to_die <= 0
		|| time_to_eat <= 0 || time_to_sleep <= 0)
		return (0);
	if (ac == 6)
	{
		must_eat = ft_atoi(av[5]);
		if (must_eat <= 0)
			return (0);
	}
	return (1);
}
