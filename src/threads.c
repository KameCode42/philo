/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:29:27 by david             #+#    #+#             */
/*   Updated: 2025/04/27 12:26:06 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// =============================================================================
// create_threads :
//
// permet de creer un thread par philo
// inclus la routine de chaque philo autour de la table
// creer le thread pour le monitoring
// lance le monitor pour verifier continuellement si un mort ou repas terminer
// le programme attend que le thread monitor_death se termine
// (soit parce qu’un philo est mort, soit parce que tout le monde a manger
// 
//
// =============================================================================
// wait_for_threads :
//
// permet d attendre qu'un thread se termine avant de continuer
// si pthread = thread 1, on attend la fin du processus thread 1, sa routine
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
