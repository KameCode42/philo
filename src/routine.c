/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:57:45 by david             #+#    #+#             */
/*   Updated: 2025/04/21 17:06:11 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	if (philo_is_dead(philo->table) == true)
		return ;
	pthread_mutex_lock(&philo->state_lock);
	philo->state = THINK;
	pthread_mutex_unlock(&philo->state_lock);
	print_state(philo, "is thinking");
}

void	philo_eat(t_philo *philo)
{
	if (philo_is_dead(philo->table) == true)
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
	if (philo_is_dead(philo->table) == true)
		return ;
	pthread_mutex_lock(&philo->state_lock);
	philo->state = SLEEP;
	pthread_mutex_unlock(&philo->state_lock);
	print_state(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

void	philo_die(t_philo *philo)
{
	if (philo->table->time_to_die < current_time() - philo->last_meal_time)
	{
		if (philo_is_dead(philo->table) == true)
		{
			pthread_mutex_lock(&philo->state_lock);
			philo->state = DEAD;
			print_state(philo, "is dead");
			pthread_mutex_unlock(&philo->state_lock);
		}
	}
}


/*
void	*routine_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	print_state(philo, "is thinking");
	while (!philo_is_dead(philo->table) && !all_philo_have_eat))
	{
	//si il pense, prend lesd fourchette
	//si il a les fork, il mange
	// si il mange, il dort
	// si il dort, il pense
	//mourir
	// check les etat
	}
	return (NULL);
}
*/