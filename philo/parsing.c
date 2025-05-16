#include "philo.h"

int valid_args(char **av, int ac)
{
    if (ac != 5 && ac != 6)
    {
        printf("Error: number of arg is not valid");
        return (0);
    }
	if (!check_digit(av))
    {
        printf("Error: Arguments must be positive numbers\n");
        return (0);
    }
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || 
        ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
    {
        printf("Error: Arguments must be positive integers\n");
        return (0);
    }
	if (ac == 6)
    {
        if (ft_atoi(av[5]) < 0 || is_empty_or_whitespace(av[5]))
        {
            printf("Error: Optional argument must be a positive number\n");
            return (0);
        }
    }
	return (0);
}