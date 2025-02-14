/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:37:37 by david             #+#    #+#             */
/*   Updated: 2025/02/14 18:31:38 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	convert_args(t_philo *philo, char **argv)
{
	philo->nbr_of_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->nbr_times_philo_eat = ft_atoi(argv[5]);
	else
		philo->nbr_times_philo_eat = -1;
	if (philo->nbr_of_philo < 1 || philo->nbr_of_philo > 200
		|| philo->time_to_die < 1 || philo->time_to_eat < 1
		|| philo->time_to_sleep < 1)
		{
			printf("Error : init failed\n");
			return (1);
		}
	return (0);
}

int	check_args(t_philo *philo, int argc, char **argv)
{
	int	i;
	int	j;

	i  = 0;
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
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error : incorrect arguments\n");
				return (1);
			}
			j++;
		}
	}
	if (convert_args(philo, argv) != 0)
		return (1);
	return (0);
}
