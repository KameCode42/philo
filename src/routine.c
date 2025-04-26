/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:57:45 by david             #+#    #+#             */
/*   Updated: 2025/04/26 16:41:39 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// =============================================================================
// routine_philo :
//
// le thread boucle en attente -> tant que start_time n'a pas ete initialiser
// une fois que create_threads est initier avec start time
// tous les threads sortent de cette boucle et demarrent en même temps
// laps de temps pour la prise de fourchette
// tant qu aucun philo est mort et que les repas ne sont pas terminer on boucle
// controle a chaque etat si un philo est mort
// sinon il pense, mange, dors ou meurt
//
// =============================================================================

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_lock);
	philo->state = THINK;
	pthread_mutex_unlock(&philo->state_lock);
	print_state(philo, "is thinking");
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_lock);
	if (philo->table->nbr_meals_eat != -1
		&& philo->meals_eaten >= philo->table->nbr_meals_eat)
	{
		pthread_mutex_unlock(&philo->state_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->state_lock);
	if (take_forks(philo) == false)
		return ;
	pthread_mutex_lock(&philo->state_lock);
	philo->state = EAT;
	philo->last_meal_time = current_time();
	philo->meals_eaten += 1;
	print_state(philo, "is eating");
	pthread_mutex_unlock(&philo->state_lock);
	ft_usleep(philo->table->time_to_eat, philo->table);
	release_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_lock);
	philo->state = SLEEP;
	pthread_mutex_unlock(&philo->state_lock);
	print_state(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

void	*routine_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (is_program_running(philo->table) == true)
	{
		if (is_program_running(philo->table) == false)
			break ;
		philo_think(philo);
		if (is_program_running(philo->table) == false)
			break ;
		philo_eat(philo);
		if (is_program_running(philo->table) == false)
			break ;
		philo_sleep(philo);
		ft_usleep(5, philo->table);
	}
	return (NULL);
}
