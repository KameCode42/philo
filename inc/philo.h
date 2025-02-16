/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:59:31 by david             #+#    #+#             */
/*   Updated: 2025/02/16 14:55:28 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_simulation //simulation globale du programme : 5 800 200 200
{
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_times_philo_eat;//nbr de repas que va manger le philo
	size_t			start_time;//calcule temps ecouler depuis le debut de la simu en ms
	pthread_mutex_t	*forks;//tableau mutex pour les fourchettes
}		t_simulation;

typedef struct s_philo
{
	int				id;//numeroter les philo
	pthread_t		thread;//represente un philo
	pthread_mutex_t	*left_fork;//ptr vers fourchette gauche
	pthread_mutex_t	*right_fork;//ptr vers fourchette droite
	t_simulation	*simulation;//ptr vers la simu globale
}		t_philo;

//utils
int		ft_atoi(const char *str);
size_t	current_time(void);
int		ft_usleep(size_t ms);

//error
int		convert_args(t_simulation *simulation, char **argv);
int		check_args(t_simulation *simulation, int argc, char **argv);

#endif