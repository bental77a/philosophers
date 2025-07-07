/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 07:24:37 by mohben-t          #+#    #+#             */
/*   Updated: 2025/07/04 06:18:36 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo_arg
{
	size_t				number_of_philosophers;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				number_of_times_philosopher_eat;
}					t_philo_arg;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	size_t				meals_eaten;
	size_t			last_meal_time;
	pthread_t		thread;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	t_philo_arg		*args;
	size_t				death_occurred;
	size_t				all_ate_enough;
	size_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	t_philo			*philos;
}					t_table;

int					valid_args(char **av, int ac);
int					init_table(t_table *table, char **av, int ac);
long				get_current_time(void);
void				cleanup_table(t_table *table);
void				print_status(t_philo *philo, char *status);
void				ft_usleep(long time_in_ms,t_philo *philo);
void				*philo_routine(void *arg);
int					start_simulation(t_table *table);
void				*ft_memset(void *b, int c, size_t len);
long					ft_atoi(const char *str);
void				handle_single_philosopher(t_philo *philo);

// free_mutex
void				fourth_destroy(t_table *table);
void				thread_destroy(t_table *table);
void				second_destroy(t_table *table);
void				first_destroy(int i, t_table *table);
#endif