/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:29:27 by david             #+#    #+#             */
/*   Updated: 2025/04/26 17:23:05 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// =============================================================================
// create_threads :
//
// permet de creer un thread par philo
// inclus la routine de chaque philo autour de la table
//
//
// =============================================================================
// wait_for_threads :
//
// permet d attendre la fin du processus appeler
// si pthread = thread 1, on attend la fin du processus thread 1
//
// ============================================================================

void	create_threads(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = current_time();
	init_philo(table);
	while (i < table->nbr_of_philo)
	{
		pthread_create(&table->philo[i].thread, NULL, routine_philo,
			&table->philo[i]);
		i++;
	}
	pthread_create(&table->monitor_thread, NULL, monitor_death, table);
	pthread_join(table->monitor_thread, NULL);
	wait_for_thread(table);
}

void	wait_for_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philo)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
}
