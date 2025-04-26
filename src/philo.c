/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:57:38 by david             #+#    #+#             */
/*   Updated: 2025/04/26 15:18:46 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// =============================================================================
// check_args :
//
// si il y a moins de 5 ou plus de 6 argument, return erreur
// si l'arg n'est pas un chiffre ou le nbr de philo est plus petit que 1
// ou si le nbr de philo est superieur a 200, return erreur
//
// =============================================================================

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Error : try with 5 or 6 arguments\n");
		return (1);
	}
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9'
				|| ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > MAX_PHILO)
			{
				printf("Error : incorrect arguments\n");
				return (1);
			}
			j++;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_args(argc, argv) != 0)
		return (1);
	init_table(&table, argv);
	create_threads(&table);
	return (0);
}
