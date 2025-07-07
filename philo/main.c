/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 07:21:32 by mohben-t          #+#    #+#             */
/*   Updated: 2025/07/02 07:23:43 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	ft_memset(&table, 0, sizeof(t_table));
	if (!valid_args(av, ac))
	{
		printf("arguments it's not be valid!!\n");
		return (0);
	}
	if (!init_table(&table, av, ac))
	{
		printf("Error: Failed to init table\n");
		cleanup_table(&table);
		return (1);
	}
	if (!start_simulation(&table))
	{
		printf("Error: Failed to start simulation\n");
		cleanup_table(&table);
		return (1);
	}
	cleanup_table(&table);
}
