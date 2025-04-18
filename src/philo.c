/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:58:22 by david             #+#    #+#             */
/*   Updated: 2025/04/17 15:21:49 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int		i;
	t_table	table;
	t_philo	philo[MAX_PHILO];

	i = 0;
	if (check_args(argc, argv) != 0)
		return (1);
	init_all(philo, &table, argv);
	create_threads(philo);
	while (i < table.nbr_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	free(table.philo);
	return (0);
}
