/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:59:31 by david             #+#    #+#             */
/*   Updated: 2025/04/11 14:13:59 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table //simulation globale du programme : 5 800 200 200 remplace par table
{
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_times_philo_eat;//nbr de repas que va manger le philo
	int				sim_end;//mettre fin a la simulation (philo mort ou tous manger)
	size_t			start_time;//calcule temps ecouler depuis le debut de la simu en ms
	pthread_mutex_t	sim_lock;//proteger contre les data races
	pthread_mutex_t	*forks;//tableau mutex pour les fourchettes
	pthread_mutex_t	*print_lock;//eviter que les printf se superpose
}		t_table;

typedef struct s_philo
{
	int				id;//numeroter les philo
	int				meals_eaten;//suivre cmb de fois un philo a manger, atteint nbr_times_philo_eat
	size_t			last_meal_time;//dernier repas de chaque philo
	pthread_t		thread;//represente un philo
	pthread_mutex_t	*left_fork;//ptr vers fourchette gauche
	pthread_mutex_t	*right_fork;//ptr vers fourchette droite
	t_table			*table;//ptr vers la simu globale
}		t_philo;

//utils
int		ft_atoi(const char *str);

//error
int		check_args(int argc, char **argv);

//time
size_t	current_time(void);
int		ft_usleep(size_t ms);

//init
void	init_table(t_table *table, char **argv);
void	init_philo(t_philo *philo, t_table *table);

#endif