/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 07:21:29 by mohben-t          #+#    #+#             */
/*   Updated: 2025/07/04 06:06:28 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_table *table)
{
	size_t	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo)
			* table->args->number_of_philosophers);
	if (!table->philos)
		return (0);
	while (i < table->args->number_of_philosophers)
	{
		table->philos[i].id = i + 1;
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = (i + 1)
			% table->args->number_of_philosophers;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = get_current_time();
		table->philos[i].table = table;
		i++;
	}
	return (1);
}

int	init_mutex(t_table *table)
{
	size_t	i;

	table->forks = malloc(sizeof(pthread_mutex_t)
			* table->args->number_of_philosophers);
	if (!table->forks)
		return (0);
	i = 0;
	while (i < table->args->number_of_philosophers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (first_destroy(i, table), 0);
		i++;
	}
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
		return (second_destroy(table), 0);
	if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
		return (thread_destroy(table), 0);
	if (pthread_mutex_init(&table->meal_mutex, NULL) != 0)
		return (fourth_destroy(table), 0);
	return (1);
}

int	init_table(t_table *table, char **av, int ac)
{
	table->args = malloc(sizeof(t_philo_arg));
	if (!table->args)
		return (0);
	table->args->number_of_philosophers = ft_atoi(av[1]);
	table->args->time_to_die = ft_atoi(av[2]);
	table->args->time_to_eat = ft_atoi(av[3]);
	table->args->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->args->number_of_times_philosopher_eat = ft_atoi(av[5]);
	else
		table->args->number_of_times_philosopher_eat = -1;
	table->death_occurred = 0;
	table->all_ate_enough = 0;
	table->start_time = get_current_time();
	if (!init_mutex(table))
		return (0);
	if (!init_philos(table))
		return (0);
	return (1);
}
