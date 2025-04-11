/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:29:48 by david             #+#    #+#             */
/*   Updated: 2025/04/11 13:30:05 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
gettimeofday() remplit cette structure avec le temps actuel
Le calcul final convertit tout en millisecondes

time.tv_sec * 1000 : convertit les secondes en millisecondes
time.tv_usec / 1000 : convertit les microsecondes en millisecondes
*/
size_t	current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
/*
Entre dans une boucle qui :

Vérifie continuellement le temps écoulé
Compare avec la durée souhaitée
Fait une micro-pause de 500 microsecondes à chaque itération
simule le temps de repas par exemple
*/
int	ft_usleep(size_t ms)
{
	size_t	start;

	start = current_time();//enregistre le temps de depart
	while ((current_time() - start) < ms)
		usleep(500);
	return (0);
}
