/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:26:27 by david             #+#    #+#             */
/*   Updated: 2025/04/12 17:16:30 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// =============================================================================
// philo_think :
//
// premier etat d un philo, il pense
// print_state : fonction qui permet de lock et unlock les print
// temps de penser 1000ms
//
// =============================================================================
// forks :
//
// philo tente de prendre la fourchette gauche
// philo tente de prendre la fourchette droite, si echoue il unlock la gauche
// sinon si fourchette droite dispo il la prend
//
// =============================================================================
// philo_eat :
//
// philo tente de prendre les fourchette (attente pour eviter crash)
// l etat du philo passe a eat
// le temps qu il mange en ms
// fini de manger, unlock les fourchette
// enregistre le temps du dernier repas
// permet de compter le nbr de repas qu un philo a manger
//
// =============================================================================
// philo_sleep :
//
// l etat du philo passe a dormir
// temps de dormir en ms
//
// =============================================================================
// routine_philo :
//
// boucle pour la simulation
//
// =============================================================================

void	philo_think(t_philo *philo)
{
	philo->state = THINK;
	print_state(philo, "is thinking");
	ft_usleep(1000);
}

bool	forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken the left fork");
	if (pthread_mutex_lock(philo->right_fork) != 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (false);
	}
	print_state(philo, "has taken the right fork");
	return (true);
}

void	philo_eat(t_philo *philo)
{
	if (!forks(philo))
	{
		ft_usleep(100);
		return ;
	}
	philo->state = EAT;
	print_state(philo, "is eating");
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->last_meal_time = current_time();
	philo->meals_eaten++;
}

void	philo_sleep(t_philo *philo)
{
	philo->state = SLEEP;
	print_state(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

void	routine_philo(t_philo *philo)
{
	while (1)
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
}
