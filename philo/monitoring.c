#include "philo.h"

void *monitor_routine(void *arg)
{
    t_table *table = (t_table *)arg;
    int i;
    long current_time;
    int all_ate = 1;
    
    while (1)
    {
        i = 0;
        all_ate = 1;
        while (i < table->args->number_of_philosophers)
        {
            pthread_mutex_lock(&table->meal_mutex);
            current_time = get_current_time();
            
            if (current_time - table->philos[i].last_meal_time > table->args->time_to_die)
            {
                pthread_mutex_unlock(&table->meal_mutex);
                pthread_mutex_lock(&table->death_mutex);
                table->death_occurred = 1;
                pthread_mutex_unlock(&table->death_mutex);
                
                pthread_mutex_lock(&table->write_mutex);
                printf("%ld %d died\n", current_time - table->start_time, table->philos[i].id);
                pthread_mutex_unlock(&table->write_mutex);
                return NULL;
            }
            if (table->args->number_of_times_philosopher_eat != -1)
            {
                if (table->philos[i].meals_eaten < table->args->number_of_times_philosopher_eat)
                    all_ate = 0;
            }
            else
                all_ate = 0;
            pthread_mutex_unlock(&table->meal_mutex);
            i++;
        }
        if (all_ate && table->args->number_of_times_philosopher_eat != -1)
        {
            pthread_mutex_lock(&table->death_mutex);
            table->all_ate_enough = 1;
            pthread_mutex_unlock(&table->death_mutex);
            return NULL;
        }
        
        usleep(1000);
    }
    return NULL;
}
int start_simulation(t_table *table)
{
    pthread_t monitor_thread;
    int i;

    i = 0;
    table->start_time = get_current_time();
    while (i < table->args->number_of_philosophers)
    {
        table->philos[i].last_meal_time = table->start_time;
        i++;
    }
    i = 0;
    while (i < table->args->number_of_philosophers)
    {
        if (pthread_create(&table->philos[i].thread, NULL, philo_routine, &table->philos[i]) != 0)
            return 0;
        i++;
    }
    if (pthread_create(&monitor_thread, NULL, monitor_routine, table) != 0)
        return 0;
    i = 0;
    while (i < table->args->number_of_philosophers)
        pthread_join(table->philos[i++].thread, NULL);
    pthread_join(monitor_thread, NULL);
    return 1;
}
