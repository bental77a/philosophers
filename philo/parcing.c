#include "philo.h"


int is_empty_or_whitespace(const char *str)
{
    if (!str || *str == '\0')
        return 1;
    while (*str)
    {
        if (*str != ' ' && *str != '\t' && *str != '\n')
            return 0;
        str++;
    }
    return 1;
}

int check_digit(char **str)
{
    int i = 0;
    while (str[i])
    {
        if (is_empty_or_whitespace(str[i]))
            return 0;
        char *s = str[i];
        while (*s)
        {
            if (*s < '0' || *s > '9')
                return 0;
            s++;
        }
        i++;
    }
    return 1;
}

int ft_atoi(const char *str)
{
    int result = 0;
    int sign = 1;
    
    while (*str == ' ' || *str == '\t' || *str == '\n')
        str++;
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
        str++;
    
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return (result * sign);
}

int valid_args(char **av, int ac)
{
    if (ac != 5 && ac != 6)
    {
        printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        return 0;
    }
    
    if (!check_digit(av + 1))
    {
        printf("Error: All arguments must be positive integers\n");
        return 0;
    }
    
    int num_philos = ft_atoi(av[1]);
    int time_to_die = ft_atoi(av[2]);
    int time_to_eat = ft_atoi(av[3]);
    int time_to_sleep = ft_atoi(av[4]);
    
    if (num_philos <= 0 || num_philos > 200 || time_to_die <= 0 || 
        time_to_eat <= 0 || time_to_sleep <= 0)
    {
        printf("Error: Invalid argument values\n");
        return 0;
    }
    
    if (ac == 6)
    {
        int must_eat = ft_atoi(av[5]);
        if (must_eat <= 0)
        {
            printf("Error: number_of_times_each_philosopher_must_eat must be positive\n");
            return 0;
        }
    }
    
    return 1;
}
