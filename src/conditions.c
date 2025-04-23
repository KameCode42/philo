/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:49:27 by david             #+#    #+#             */
/*   Updated: 2025/04/23 11:08:52 by dle-fur          ###   ########.fr       */
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

bool	philo_is_dead(t_philo *philo)
{
	size_t	time_since_last_meal;

	pthread_mutex_lock(&philo->state_lock);
	time_since_last_meal = current_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->state_lock);
	if (time_since_last_meal >= philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->death_lock);
		if (philo->table->someone_died == false)
		{
			print_state(philo, "is dead");
			philo->table->someone_died = true;
		}
		pthread_mutex_unlock(&philo->table->death_lock);
		return (true);
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
