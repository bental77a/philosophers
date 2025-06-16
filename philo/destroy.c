#include "philo.h"

void first_destroy(int i, t_table *table)
{
    while (--i >= 0)
        pthread_mutex_destroy(&table->forks[i]);
    free(table->forks);
}

void second_destroy(t_table *table)
{
    int i;

    i = 0;
    while (i < table->args->number_of_philosophers)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    free(table->forks);
}

void thread_destroy(t_table *table)
{
    int i;

    pthread_mutex_destroy(&table->write_mutex);
    i = 0;
    while (i < table->args->number_of_philosophers)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    free(table->forks);
}

void fourth_destroy(t_table *table)
{
    int i;

    pthread_mutex_destroy(&table->death_mutex);
    pthread_mutex_destroy(&table->write_mutex);
    i = 0;
    while (i < table->args->number_of_philosophers)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    free(table->forks);
}
