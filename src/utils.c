/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:31:08 by david             #+#    #+#             */
/*   Updated: 2025/04/12 17:17:42 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// =============================================================================
// current_time :
//
// gettimeofday() remplit cette structure avec le temps actuel
// le calcul final convertit tout en millisecondes
// time.tv_sec * 1000 : convertit les secondes en millisecondes
// time.tv_usec / 1000 : convertit les microsecondes en millisecondes
//
// =============================================================================
// ft_usleep :
//
// enregistre le temps de depart
// entre dans une boucle qui :
// vérifie continuellement le temps écoulé
// compare avec la durée souhaitée
// fait une micro-pause de 500 microsecondes à chaque itération
// simule le temps de repas par exemple
//
// =============================================================================

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			sign = -sign;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

void	print_state(t_philo *philo, const char *message)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("Philosopher %d %s\n", philo->id, message);
	pthread_mutex_unlock(&philo->table->print_lock);
}

size_t	current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = current_time();
	while ((current_time() - start) < ms)
		usleep(500);
	return (0);
}
