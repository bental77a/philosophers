#include "philo.h"


int main(char ac, char **av)
{

    t_table table;
    //set table 0
    ft_memset(&table, 0, sizeof(t_table));
    //parse input
    if (!valid_args(av,ac))
        printf("arguments it's not be valid!!\n");
    //init table (mutex and philos)
    if (!init_table(&table, av, ac))
    {
        printf("Error: Failed to init table\n");
        cleanup_table(&table);//clean all of things
        return (1);
    }
    //simulation
    if (!start_simulation(&table))
    {
        printf("Error: Failed to start simulation\n");
        cleanup_table(&table);
        return 1;
    }
    cleanup_table(&table);
    
}