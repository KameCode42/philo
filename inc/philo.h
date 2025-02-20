/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:59:31 by david             #+#    #+#             */
/*   Updated: 2025/02/18 19:26:09 by dle-fur          ###   ########.fr       */
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
	size_t			start_time;//calcule temps ecouler depuis le debut de la simu en ms
	pthread_mutex_t	*forks;//tableau mutex pour les fourchettes
	pthread_mutex_t	*print_lock;//eviter que les printf se superpose
}		t_table;

typedef struct s_philo
{
	int				id;//numeroter les philo
	int				*philos;
	pthread_t		thread;//represente un philo
	pthread_mutex_t	*left_fork;//ptr vers fourchette gauche
	pthread_mutex_t	*right_fork;//ptr vers fourchette droite
	//t_table			*table;//ptr vers la simu globale
}		t_philo;

//utils
int		ft_atoi(const char *str);
size_t	current_time(void);
int		ft_usleep(size_t ms);

//error
int		check_args(int argc, char **argv);

#endif