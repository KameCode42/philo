/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:49:27 by david             #+#    #+#             */
/*   Updated: 2025/04/25 10:59:12 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// =============================================================================
// check_philo_dead :
//
// time_since_last_meal = temps sans manger
// time_since_last_meal = temps actuel - dernier repas
// exemple :                   12h            10h    = 2h
// donc philo mange toute les 2h sinon il meurt
// si un philo meurt fin de la simulation
//
// =============================================================================
// all_philo_have_eat :
//
// si pas d'option de nombre de repas, return false
// meals_eaten permet de suivre le nombre de repas que le philo mange
// si un philosophe n’a pas assez manger, retourne false -> simulation continue
// sinon return true si atteint
//
// =============================================================================

bool	philo_is_dead(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philo)
	{
		pthread_mutex_lock(&table->philo[i].state_lock);
		if (table->philo[i].state == DEAD)
		{
			pthread_mutex_unlock(&table->philo[i].state_lock);
			return (true);
		}
		pthread_mutex_unlock(&table->philo[i].state_lock);
		i++;
	}
	return (false);
}

bool	all_philo_have_eat(t_table *table)
{
	int	i;

	if (table->nbr_meals_eat == -1)
		return (false);
	i = 0;
	while (i < table->nbr_of_philo)
	{
		pthread_mutex_lock(&table->philo[i].state_lock);
		if (table->philo[i].meals_eaten < table->nbr_meals_eat)
		{
			pthread_mutex_unlock(&table->philo[i].state_lock);
			return (false);
		}
		pthread_mutex_unlock(&table->philo[i].state_lock);
		i++;
	}
	return (true);
}
