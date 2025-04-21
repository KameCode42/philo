/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:47:40 by david             #+#    #+#             */
/*   Updated: 2025/04/21 16:22:31 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// =============================================================================
// forks_order :
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
// take_forks :
//
// check si un philo est mort si oui arrete de la simulation
// on check l'ordre des forks
// si les forks sont lock, l'etat du philo passe a manger
// dernier repas = temps actuel
//
// =============================================================================

bool	take_first_fork(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->fork_lock) != 0)
		return (false);
	print_state(philo, "has taken a fork");
	return (true);
}

bool	take_second_fork(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->next->fork_lock) != 0)
		return (false);
	print_state(philo, "has taken a fork");
	return (true);
}

bool	forks_order(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (take_first_fork(philo->next) == false)
			return (false);
		if (take_second_fork(philo) == false)
		{
			pthread_mutex_unlock(&philo->next->fork_lock);
			return (false);
		}
	}
	else
	{
		if (take_first_fork(philo) == false)
			return (false);
		if (take_second_fork(philo->next) == false)
		{
			pthread_mutex_unlock(&philo->fork_lock);
			return (false);
		}
	}
	return (true);
}

bool	take_forks(t_philo *philo)
{
	if (forks_order(philo) == false)
		return (false);
	return (true);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork_lock);
	pthread_mutex_unlock(&philo->next->fork_lock);
}
