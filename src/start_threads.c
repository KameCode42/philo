/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:26:07 by dle-fur           #+#    #+#             */
/*   Updated: 2025/04/17 15:03:29 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_create(&philo->table->monitoring, NULL, monitoring_simulation, &philo->table);
	while (i < philo->table->nbr_of_philo)
	{
		pthread_create(&philo[i].thread, NULL, routine_philo, &philo[i]);
		i++;
	}
	ft_usleep(100);
}
