/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:12:20 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/14 19:51:34 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO
# define FT_PHILO

// Standard Libraries
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdatomic.h>
# include <stdbool.h>

typedef struct s_philo_arg
{
    int             number_of_philosophers;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             number_of_times_philosopher_eat;
}                   t_philo_arg;

typedef struct s_philo
{
    int             id;
    int             left_fork;
    int             right_fork;
    int             meals_eaten;
    long            last_meal_time;//for finishing project
    pthread_t       thread;
    struct s_table  *table;
}                   t_philo;

typedef struct s_table
{
    t_philo_arg     *args;
    int             death_occurred;
    int             all_ate_enough;
    long            start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t write_mutex;
    pthread_mutex_t death_mutex;
    pthread_mutex_t meal_mutex;
    t_philo         *philos;
}                   t_table;

int valid_args(char **av, int ac);
int init_table(t_table *table, char **av, int ac);
long get_current_time(void);
void cleanup_table(t_table *table);
void print_status(t_philo *philo, char *status);
void ft_usleep(long time_in_ms);
void *philo_routine(void *arg);
int start_simulation(t_table *table);
void	*ft_memset(void *b, int c, size_t len);
int ft_atoi(const char *str);

#endif