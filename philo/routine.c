#include "philo.h"

void take_forks(t_philo *philo)
{
    int first_fork;
    int second_fork;

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
void eat(t_philo *philo)
{
    take_forks(philo);
    pthread_mutex_lock(&philo->table->meal_mutex);
    philo->last_meal_time = get_current_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->table->meal_mutex);
    print_status(philo, "is eating");
    ft_usleep(philo->table->args->time_to_eat);
    pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
    pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}
void philo_sleep(t_philo *philo)
{
    print_status(philo, "is sleeping");
    ft_usleep(philo->table->args->time_to_sleep);
}

void think(t_philo *philo)
{
    print_status(philo, "is thinking");
}
void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        ft_usleep(philo->table->args->time_to_eat / 2);
    while (1)
    {
        pthread_mutex_lock(&philo->table->death_mutex);
        if (philo->table->death_occurred || philo->table->all_ate_enough)
        {
            pthread_mutex_unlock(&philo->table->death_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->table->death_mutex);
        
        eat(philo);
        philo_sleep(philo);
        think(philo);
    }
    return NULL;
}
