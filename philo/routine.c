/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 07:21:48 by mohben-t          #+#    #+#             */
/*   Updated: 2025/07/08 11:16:50 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	pthread_mutex_lock(&philo->table->forks[first_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->forks[second_fork]);
	print_status(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	print_status(philo, "is eating");
	ft_usleep(philo->table->args->time_to_eat,philo);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->table->args->time_to_sleep,philo);
}
static void	philo_think(t_philo *philo)
{
	long	time_since_meal;
	long	time_left;
	long	think_time;

	if (philo->table->args->number_of_philosophers % 2)
	{
		pthread_mutex_lock(&philo->table->death_mutex);
		time_since_meal = get_current_time() - philo->last_meal_time;
		time_left = philo->table->args->time_to_die - time_since_meal;
		pthread_mutex_unlock(&philo->table->death_mutex);
		if (time_left > 0)
		{
			think_time = (long)(time_left * 0.9);
			if (think_time > 0)
				ft_usleep(think_time, philo);
		}
	}
}
void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->args->number_of_philosophers == 1)
		return (handle_single_philosopher(philo), NULL);
	while (1)
	{
		pthread_mutex_lock(&philo->table->death_mutex);
		if (philo->table->death_occurred || philo->table->all_ate_enough)
		{
			pthread_mutex_unlock(&philo->table->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->death_mutex);
		eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		think(philo);
	}
	return (NULL);
}
/*
static void	philo_think(t_philos *philo)
{
	long	time_since_meal;
	long	time_left;
	long	think_time;

	if (philo->data->number_of_philosophers % 2)
	{
		pthread_mutex_lock(philo->data->death_mutex);
		time_since_meal = get_current_time() - philo->last_meal_time;
		time_left = philo->data->time_to_die - time_since_meal;
		pthread_mutex_unlock(philo->data->death_mutex);
		if (time_left > 0)
		{
			think_time = (long)(time_left * 0.9);
			if (think_time > 0)
				ft_usleep(think_time, philo);
		}
	}
}*/