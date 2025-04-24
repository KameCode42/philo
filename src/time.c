/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:57:44 by david             #+#    #+#             */
/*   Updated: 2025/04/24 13:54:57 by david            ###   ########.fr       */
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
	while (current_time() - start < ms)
		usleep(500);
	return (0);
}
