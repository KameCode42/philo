/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:49:27 by david             #+#    #+#             */
/*   Updated: 2025/04/27 12:46:09 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// =============================================================================
// check_philo_death :
//
// si un philo n'est pas deja mort et que le temps du dernier repas est
// plus grand que le temps de mort le philo meurt on arrete le prgramme
//
// =============================================================================
// monitor_death :
//
// permet de verifier continuellment si un philo est mort et prend en compte
// le nombre de repas (option)
// si un mort on arrete le programme avec check_philo_death
// si le nombre de repas est atteint, program_run = false
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

bool	check_philo_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_lock);
	if (philo->state != DEAD
		&& current_time() - philo->last_meal_time >= philo->table->time_to_die)
	{
		philo->state = DEAD;
		print_state(philo, "died");
		pthread_mutex_lock(&philo->table->death_lock);
		philo->table->program_run = false;
		pthread_mutex_unlock(&philo->table->death_lock);
		pthread_mutex_unlock(&philo->state_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->state_lock);
	return (false);
}

void	*monitor_death(void *param)
{
	t_table	*table;
	int		i;

	table = (t_table *)param;
	while (is_program_running(table))
	{
		i = 0;
		while (i < table->nbr_of_philo)
		{
			if (check_philo_death(&table->philo[i]))
				return (NULL);
			i++;
		}
		if (all_philo_have_eat(table))
		{
			pthread_mutex_lock(&table->death_lock);
			table->program_run = false;
			pthread_mutex_unlock(&table->death_lock);
			return (NULL);
		}
		ft_usleep(1, table);
	}
	return (NULL);
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
