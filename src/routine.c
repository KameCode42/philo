/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:57:45 by david             #+#    #+#             */
/*   Updated: 2025/04/25 13:24:58 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// =============================================================================
// routine_philo :
//
// 1 -> philo pense
// 2 -> il mange
// 3 -> apres manger, il dort
// 4 -> il repense
// si il y a un mort la simulation s'arrete
//
// =============================================================================

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
	size_t	time_since_last_meal;

	pthread_mutex_lock(&philo->state_lock);
	time_since_last_meal = current_time() - philo->last_meal_time;
	if (philo->state != DEAD
		&& time_since_last_meal >= philo->table->time_to_die)
	{
		philo->state = DEAD;
		print_state(philo, "died");
	}
	pthread_mutex_unlock(&philo->state_lock);
}

void	*routine_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (philo->table->start_time == 0)
		usleep(50);
	philo_think(philo);
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (!philo_is_dead(philo->table) && !all_philo_have_eat(philo->table))
	{
		philo_die(philo);
		philo_eat(philo);
		philo_die(philo);
		philo_sleep(philo);
		philo_die(philo);
		philo_think(philo);
		ft_usleep(5);
	}
	return (NULL);
}
