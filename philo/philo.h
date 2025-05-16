/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:12:20 by mohben-t          #+#    #+#             */
/*   Updated: 2025/05/15 14:18:55 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef FT_PHILO
// # define FT_PHILO


// # include <limits.h>
// # include <pthread.h>
// # include <stdio.h>
// # include <string.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <sys/time.h>




// # define SUCCESS 1
// # define FAILURE 0


// int	ft_atoi(const char *str);
// int	check_digit(char **str);


// int		valid_args(char **av, int ac);
// int		is_empty_or_whitespace(const char *str);
// void init_struct(t_info *philo, int num_philo, char **av);

// #endif


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

// Return Codes
# define SUCCESS 1
# define FAILURE 0

// Forward Declarations
typedef struct s_info t_info;
typedef struct s_fork t_fork;
typedef struct s_philo t_philo;

// Fork Structure
typedef struct s_fork
{
    pthread_mutex_t mutex;
    int             fork_id;
}   t_fork;

// Philosopher Structure
typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    atomic_bool     is_dead;
    bool            full;
    
    // Meal Tracking
    int             meals_counter;
    long long       last_meal_time;

    // Resource Pointers
    t_fork          *left_fork;
    t_fork          *right_fork;
    t_info          *info;
}   t_philo;

// Simulation Information Structure
typedef struct s_info
{
    // Simulation Parameters
    int             num_philo;
    int             time_die;
    int             time_eat;
    int             time_slep;
    int             limit_meals;

    // Simulation Control
    long long       start_time;
    atomic_bool     end_simulation;

    // Resources
    t_fork          *forks;
    t_philo         *philos;

    // Synchronization Mutexes
    pthread_mutex_t print_mutex;
    pthread_mutex_t end_mutex;
}   t_info;

int     valid_args(char **av, int ac);
int     check_digit(char **str);
int     is_empty_or_whitespace(const char *str);
int     ft_atoi(const char *str);
long long get_current_time(void);
void    init_struct(t_info *philo, int num_philo, char **av);

#endif