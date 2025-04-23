/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:47:40 by david             #+#    #+#             */
/*   Updated: 2025/04/23 11:11:09 by dle-fur          ###   ########.fr       */
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
