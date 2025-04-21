/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:49:27 by david             #+#    #+#             */
/*   Updated: 2025/04/21 16:49:46 by david            ###   ########.fr       */
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
	size_t	time_since_last_meal;

	pthread_mutex_lock(&table->philo->state_lock);
	time_since_last_meal = current_time() - table->philo->last_meal_time;
	if (time_since_last_meal > table->time_to_die)
	{
		table->philo->state = DEAD;
		pthread_mutex_unlock(&table->philo->state_lock);
		return (true);
	}
	pthread_mutex_unlock(&table->philo->state_lock);
	return (false);
}

bool	all_philo_have_eat(t_table *table)
{
	if (table->nbr_meals_eat == -1)
		return (false);
	pthread_mutex_lock(&table->philo->state_lock);
	if (table->philo->meals_eaten < table->philo->table->nbr_meals_eat)
	{
		pthread_mutex_unlock(&table->philo->state_lock);
		return (false);
	}
	pthread_mutex_unlock(&table->philo->state_lock);
	return (true);
}
