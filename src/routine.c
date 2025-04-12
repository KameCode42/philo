/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:26:27 by david             #+#    #+#             */
/*   Updated: 2025/04/12 15:09:34 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	philo->state = THINK;
	print_state(philo, "is thinking");
	ft_usleep(1000);//le temps a penser
}

bool	forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken the left fork");
	if (pthread_mutex_lock(philo->right_fork) != 0)//si fourchette droite pas dispo
	{
		pthread_mutex_unlock(philo->left_fork);
		return false;
	}
	print_state(philo, "has taken the right fork");
	return true;
}

void	philo_eat(t_philo *philo)
{
	if (!forks(philo))
	{
		ft_usleep(100);//evite crash
		return ;
	}
	philo->state = EAT;
	print_state(philo, "is eating");
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->last_meal_time = current_time();//enregistre le temps du dernier repas
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
