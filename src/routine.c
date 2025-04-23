  /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:57:45 by david             #+#    #+#             */
/*   Updated: 2025/04/22 15:40:55 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	if (philo_is_dead(philo) == true)
		return ;
	pthread_mutex_lock(&philo->state_lock);
	philo->state = THINK;
	pthread_mutex_unlock(&philo->state_lock);
	print_state(philo, "is thinking");
}

void	philo_eat(t_philo *philo)
{
	if (philo_is_dead(philo) == true)
		return ;
	if (take_forks(philo) == false)
		return ;
	pthread_mutex_lock(&philo->state_lock);
	philo->state = EAT;
	philo->last_meal_time = current_time();
	philo->meals_eaten += 1;
	print_state(philo, "is eating");
	pthread_mutex_unlock(&philo->state_lock);
	ft_usleep(philo->table->time_to_eat);
	release_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	if (philo_is_dead(philo) == true)
		return ;
	pthread_mutex_lock(&philo->state_lock);
	philo->state = SLEEP;
	pthread_mutex_unlock(&philo->state_lock);
	print_state(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

void	*routine_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	philo_think(philo);
	while (!philo_is_dead(philo) && !all_philo_have_eat(philo->table))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}




/*
void	*routine_philo(void *param)
{
	t_philo *philo;

	philo = (t_philo *)param;

	// Délaie de quelques microsecondes pour éviter la synchronisation parfaite (optionnel)
	if (philo->id % 2 == 0)
		usleep(100);

	// Boucle principale, s'arrête si le philosophe est mort ou a mangé le nombre suffisant de repas
	while (!philo_is_dead(philo) && !all_philo_have_eat(philo->table))
	{
		// Philosophe pense
		philo_think(philo);
		if (philo_is_dead(philo)) // Si le philosophe est mort après avoir pensé, on arrête
			break;

		// Philosophe mange
		philo_eat(philo);
		if (philo_is_dead(philo)) // Si le philosophe est mort après avoir mangé, on arrête
			break;

		// Philosophe dort
		philo_sleep(philo);
		if (philo_is_dead(philo)) // Si le philosophe est mort après avoir dormi, on arrête
			break;
	}

	return (NULL);
}

*/