/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:07:04 by david             #+#    #+#             */
/*   Updated: 2025/04/30 17:48:37 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// =============================================================================
// init_table :
//
// argv[6] = option de nombre de repas
// init les argv et les convertit
// program_run -> booleen pour l arret ou non du programme
//
// =============================================================================
// init_philo :
//
// id permet d'identifier le philo (philo commence a 1)
// combien de fois un philo a manger
// permet au philo de partir au meme point de demarrage
// init thread par philo
// init le mutex fork_lock
// etat du debut d'un philo = penser
// init le mutex print_lock
// philo[i] a acces a la structure table
// permet d'assigner le bon nombre de philo et fourchette
// si 5 philo : 5 % 5 == 0 on revient au debut
//
// =============================================================================

void	init_table(t_table *table, char **argv)
{
	table->nbr_of_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->nbr_meals_eat = ft_atoi(argv[5]);
	else
		table->nbr_meals_eat = -1;
	table->start_time = current_time();
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->death_lock, NULL);
	table->program_run = true;
}

void	init_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		table->philo[i].last_meal_time = table->start_time;
		table->philo[i].thread = 0;
		pthread_mutex_init(&table->philo[i].fork_lock, NULL);
		table->philo[i].state = THINK;
		pthread_mutex_init(&table->philo[i].state_lock, NULL);
		table->philo[i].table = table;
		table->philo[i].next = &table->philo[(i + 1) % table->nbr_of_philo];
		i++;
	}
}
