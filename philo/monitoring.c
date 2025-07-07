/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 07:21:23 by mohben-t          #+#    #+#             */
/*   Updated: 2025/07/07 16:52:49 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher_death(t_table *table, int i, long current_time)
{
	if (current_time 
		- table->philos[i].last_meal_time > table->args->time_to_die)
	{
		pthread_mutex_lock(&table->death_mutex);
		table->death_occurred = 1;
		pthread_mutex_unlock(&table->death_mutex);
		pthread_mutex_lock(&table->write_mutex);
		printf("%ld %d died\n", current_time - table->start_time,
			table->philos[i].id);
		pthread_mutex_unlock(&table->write_mutex);
		return (1);
	}
	return (0);
}

int	check_all_ate_enough(t_table *table, size_t *all_ate)
{
	size_t	i;

	i = -1;
	if (table->args->number_of_times_philosopher_eat == i)
	{
		*all_ate = 0;
		return (0);
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	long	current_time;

	size_t (i), (all_ate) ,(j);
	j = -1;
	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		all_ate = 1;
		while (i < table->args->number_of_philosophers)
		{
			pthread_mutex_lock(&table->meal_mutex);
			current_time = get_current_time();
			if (check_philosopher_death(table, i, current_time))
				return (pthread_mutex_unlock(&table->meal_mutex), NULL);
			if (table->args->number_of_times_philosopher_eat != j
				&& table->philos[i].meals_eaten < table->args->number_of_times_philosopher_eat)
				all_ate = 0;
			else if (table->args->number_of_times_philosopher_eat == j)
				all_ate = 0;
			pthread_mutex_unlock(&table->meal_mutex);
			i++;
		}
		if (all_ate && table->args->number_of_times_philosopher_eat != j)
		{
			pthread_mutex_lock(&table->death_mutex);
			table->all_ate_enough = 1;
			return (pthread_mutex_unlock(&table->death_mutex), NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	pthread_t	monitor_thread;
	size_t			i;

	i = 0;
	while (i < table->args->number_of_philosophers)
	{
		table->philos[i].last_meal_time = table->start_time;
		i++;
	}
	i = 0;
	while (i < table->args->number_of_philosophers)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine,
				&table->philos[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, table) != 0)
		return (0);
	i = 0;
		while (i < table->args->number_of_philosophers)
			pthread_join(table->philos[i++].thread, NULL);
	pthread_join(monitor_thread, NULL);
	return (1);
}
void	handle_single_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	ft_usleep(philo->table->args->time_to_die + 100,philo);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
}
