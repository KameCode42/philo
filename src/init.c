/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:07:04 by david             #+#    #+#             */
/*   Updated: 2025/04/11 14:19:46 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table, char **argv)
{
	table->nbr_of_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->nbr_times_philo_eat = ft_atoi(argv[5]);
	else
		table->nbr_times_philo_eat = -1;
	table->start_time = 0;
}

//int	init_mutex(t_philo *philo, t_table *table)

void	init_philo(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philo - 1)
	{
		philo[i].id = i + 1;//0 + 1, si 5 philo 4 + 1, arret
		philo[i].table = table;//philo[i] a acces a la struct table
		philo[i].meals_eaten = table->nbr_times_philo_eat;//cmb de fois un philo mange
		philo[i].left_fork = &table->forks[i];//assigne fourchette gauche
		philo[i].right_fork = &table->forks[i + 1];//assigne fourchette gauche
		philo[i].last_meal_time = table->start_time;
		i++;
	}
}
