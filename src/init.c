/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:07:04 by david             #+#    #+#             */
/*   Updated: 2025/04/17 15:02:46 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// =============================================================================
// init_table :
//
// permet de convertir l'entree de l'utilisateur en int et d'init la table
//
// =============================================================================
// init_mutex :
//
// important d'utiliser pthread_mutex_init
// init le mutex globale avec sim_lock (protege contre les data races)
// init les fourchette par rapport au nbr de philo (3 philo = 3 fourchettes)
// init le mutex pour l'affichage, evite les print de se superposer
//
// =============================================================================
// init_philo :
//
// id permet d'identifier le philo (0 + 1, si 5 philo 4 + 1, arret)
// philo[i] a acces a la struct table
// init cmb de fois un philo a manger
// dernier repas = start time (tant que le philo a pas manger = last meal)
// assigne la fouchette gauche
// assigne fourchette droite (utilise le modulo pour revenir au debut)
// exemple : si 5 philo, le dernier philo a la fourchette 4 et 0 (pas 4 et 5)
// philo 0,1,2,3,4 -> fourchette 0,1,2,3,4
//
// =============================================================================

void	init_table(t_table *table, char **argv)
{
	table->philo = ft_calloc(ft_atoi(argv[1]), sizeof(t_philo));
	if (!table->philo)
		return ;
	table->nbr_of_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->nbr_times_philo_eat = ft_atoi(argv[5]);
	else
		table->nbr_times_philo_eat = -1;
	table->start_time = current_time();
	table->sim_end = 0;
}

void	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_init(&table->sim_lock, NULL);
	while (i < table->nbr_of_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->print_lock, NULL);
}

void	init_philo(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].table = table;
		philo[i].meals_eaten = 0;
		philo[i].last_meal_time = table->start_time;
		philo[i].left_fork = &table->forks[i];
		philo[i].right_fork = &table->forks[(i + 1) % table->nbr_of_philo];
		i++;
	}
}

void	init_all(t_philo *philo, t_table *table, char **argv)
{
	init_table(table, argv);
	init_mutex(table);
	init_philo(philo, table);
}
