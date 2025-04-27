/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:47:40 by david             #+#    #+#             */
/*   Updated: 2025/04/27 12:38:32 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// =============================================================================
// take_forks :
//
// pour chaque action on check si un mort survient
//
// permet d'eviter les data races -> action qu un philo ne peut pas faire
// exemple si deux philo choppe la meme fourchette c est un data race
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
// impairs : left → right
// pairs : right → left
//
// =============================================================================

bool	take_forks_peer(t_philo *philo)
{
	if (is_program_running(philo->table) == false)
		return (false);
	if (pthread_mutex_lock(&philo->next->fork_lock) != 0)
		return (false);
	print_state(philo, "has taken a fork");
	if (is_program_running(philo->table) == false)
	{
		pthread_mutex_unlock(&philo->next->fork_lock);
		return (false);
	}
	if (philo == philo->next)
	{
		ft_usleep(philo->table->time_to_die, philo->table);
		pthread_mutex_unlock(&philo->next->fork_lock);
		return (false);
	}
	if (pthread_mutex_lock(&philo->fork_lock) != 0)
	{
		pthread_mutex_unlock(&philo->next->fork_lock);
		return (false);
	}
	print_state(philo, "has taken a second fork");
	return (true);
}

bool	take_forks_odd(t_philo *philo)
{
	if (is_program_running(philo->table) == false)
		return (false);
	if (pthread_mutex_lock(&philo->fork_lock) != 0)
		return (false);
	print_state(philo, "has taken a fork");
	if (is_program_running(philo->table) == false)
	{
		pthread_mutex_unlock(&philo->fork_lock);
		return (false);
	}
	if (philo == philo->next)
	{
		ft_usleep(philo->table->time_to_die, philo->table);
		pthread_mutex_unlock(&philo->fork_lock);
		return (false);
	}
	if (pthread_mutex_lock(&philo->next->fork_lock) != 0)
	{
		pthread_mutex_unlock(&philo->fork_lock);
		return (false);
	}
	print_state(philo, "has taken a second fork");
	return (true);
}

bool	take_forks(t_philo *philo)
{
	if (is_program_running(philo->table) == false)
		return (false);
	if (philo->id % 2 == 0)
		return (take_forks_peer(philo));
	else
		return (take_forks_odd(philo));
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork_lock);
	pthread_mutex_unlock(&philo->next->fork_lock);
}
