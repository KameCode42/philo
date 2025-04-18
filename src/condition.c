/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:30:01 by david             #+#    #+#             */
/*   Updated: 2025/04/17 14:49:40 by dle-fur          ###   ########.fr       */
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
// si un philo meurt fin de la simu
//
// =============================================================================
// all_philo_have_eat :
//
// meals_eaten permet de suivre le nombre de repas que le philo mange
// si le nombre de repas n est pas atteint, return false
// sinon return true si atteint
//
// =============================================================================

bool	check_philo_dead(t_philo *philo)
{
	int		i;
	size_t	time_since_last_meal;

	i = 0;
	while (i < philo->table->nbr_of_philo)
	{
		time_since_last_meal = current_time() - philo[i].last_meal_time;
		if (time_since_last_meal > philo->table->time_to_die)
		{
			philo[i].state = DEAD;
			print_state(&philo[i], "is dead");
			return (true);
		}
		i++;
	}
	return (false);
}

bool	all_philo_have_eat(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->nbr_of_philo)
	{
		if (philo[i].meals_eaten < philo[i].table->nbr_times_philo_eat)
			return (false);
		i++;
	}
	return (true);
}

void	*monitoring_simulation(void *param)
{
	t_table *table;

	table = (t_table *)param;
	while (table->sim_end == 0)
	{
		if (check_philo_dead(table->philo) == true)
		{
			table->sim_end = 1;
			break ;
		}
		if (all_philo_have_eat(table->philo) == true)
		{
			table->sim_end = 1;
			break ;
		}
		ft_usleep(500);
	}
	return (NULL);
}
