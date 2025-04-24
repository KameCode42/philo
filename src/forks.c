/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:47:40 by david             #+#    #+#             */
/*   Updated: 2025/04/24 11:17:29 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// =============================================================================
// take_forks :
//
// permet de verifier l'ordre des prise de fourchette pour chaque philo
// pour 4 philosophes -> regle pair/impair
//
// Philosophe 1 (1 % 2 == 1 → impair)
// Prend d’abord la fourchette gauche
// Puis la fourchette droite
//
// Philosophe 2 (2 % 2 == 0 → pair)
// Prend d’abord la fourchette droite
// Puis la fourchette gauche
//
// Philosophe 3 (3 % 2 == 1 → impair)
// Prend d’abord la fourchette gauche
// Puis la fourchette droite
//
// Philosophe 4 (4 % 2 == 0 → pair)
// Prend d’abord la fourchette droite
// Puis la fourchette gauche
//
// =============================================================================

bool	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->next->fork_lock) != 0)
			return (false);
		print_state(philo, "has taken a fork");
		if (pthread_mutex_lock(&philo->fork_lock) != 0)
		{
			pthread_mutex_lock(&philo->next->fork_lock);
			return (false);
		}
		print_state(philo, "has taken a second fork");
	}
	else
	{
		if (pthread_mutex_lock(&philo->fork_lock) != 0)
			return (false);
		print_state(philo, "has taken a fork");
		if (pthread_mutex_lock(&philo->next->fork_lock) != 0)
		{
			pthread_mutex_unlock(&philo->fork_lock);
			return (false);
		}
		print_state(philo, "has taken a second fork");
	}
	return (true);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork_lock);
	pthread_mutex_unlock(&philo->next->fork_lock);
}
