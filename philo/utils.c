#include "philo.h"


static int ft_isdigit(int ascii_nbr)
{
    return (ascii_nbr >= '0' && ascii_nbr <= '9');
}

int	check_digit(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		if (res > INT_MAX)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
        return (-1);
	return ((int)res);
}
int is_empty_or_whitespace(const char *str)
{
    int i;

    if (!str)
        return (1);
    i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' &&
            str[i] != '\v' && str[i] != '\f' && str[i] != '\r')
            return (0);
        i++;
    }
    return (1);
}

void init_struct(t_info *info, int num_philo, char **av)
{
    int i;
    info->num_philo = num_philo;
    info->time_die = ft_atoi(av[2]);
    info->time_eat = ft_atoi(av[3]);
    info->time_slep = ft_atoi(av[4]);
    info->limit_meals = (av[5]) ? ft_atoi(av[5]) : -1;
    info->end_simulation = false;
    info->start_time = get_current_time();
    info->forks = malloc(num_philo * sizeof(t_fork));
    info->philos = malloc(num_philo * sizeof(t_philo));
    pthread_mutex_init(&info->print_mutex, NULL);
    pthread_mutex_init(&info->end_mutex, NULL);
    i = 0;
    while (i < num_philo)
    {
        info->forks[i].fork_id = i;
        pthread_mutex_init(&info->forks[i].mutex, NULL);
        i++;
    }
    i = 0;
    while (i < num_philo)
    {
        info->philos[i].id = i;
        info->philos[i].info = info;
        info->philos[i].full = false;
        info->philos[i].meals_counter = 0;
        info->philos[i].left_fork = &info->forks[i];
        info->philos[i].right_fork = &info->forks[(i + 1) % num_philo];
        i++;
    }
}
