/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 07:21:50 by mohben-t          #+#    #+#             */
/*   Updated: 2025/07/07 16:58:05 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_table(t_table *table)
{
	size_t	i;

	i = 0;
	if (table->forks)
	{
		while (i < table->args->number_of_philosophers)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	if (table->philos)
		free(table->philos);
	if (table->args)
		free(table->args);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->table->write_mutex);
	pthread_mutex_lock(&philo->table->death_mutex);
	if (!philo->table->death_occurred)
	{
		printf("%ld %d %s\n", get_current_time() - philo->table->start_time,
			philo->id, status);
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

void	ft_usleep(long time_in_ms,t_philo *philo)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < time_in_ms)
	{
		pthread_mutex_lock(&philo->table->death_mutex);
		if (philo->table->death_occurred == 1)
		{
			pthread_mutex_unlock(&philo->table->death_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->table->death_mutex);
	}
		usleep(100);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
		ptr[i++] = (unsigned char)c;
	return (b);
}
