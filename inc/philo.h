/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:59:31 by david             #+#    #+#             */
/*   Updated: 2025/04/12 15:10:33 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// =============================================================================
// struct s_table :
//
// simulation globale du programme : 5 800 200 200 (7) remplace par table
// nbr de repas que va manger le philo
// mettre fin a la simulation (philo mort ou tous manger)
// calcule temps ecouler depuis le debut de la simu en ms
// proteger contre les data races
// tableau mutex pour les fourchettes
// eviter que les printf se superpose
//
// =============================================================================
// struct s_philo :
//
// numeroter les philo
// suivre cmb de fois un philo a manger, atteint nbr_times_philo_eat
// dernier repas de chaque philo
// represente un philo
// ptr vers fourchette gauche
// ptr vers fourchette droite
// ptr vers les enums
// ptr vers la simu globale
//
// =============================================================================

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

# define MAX_PHILO 200

typedef enum e_philo_state
{
	EAT,
	SLEEP,
	THINK,
	DEAD
}		t_philo_state;

typedef struct s_table
{
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_times_philo_eat;
	int				sim_end;
	size_t			start_time;
	pthread_mutex_t	sim_lock;
	pthread_mutex_t	forks[MAX_PHILO];
	pthread_mutex_t	print_lock;
}		t_table;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	size_t			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_philo_state	state;
	t_table			*table;
}		t_philo;

//utils
int		ft_atoi(const char *str);
void	print_state(t_philo *philo, const char *message);

//error
int		check_args(int argc, char **argv);

//time
size_t	current_time(void);
int		ft_usleep(size_t ms);

//init
void	init_table(t_table *table, char **argv);
void	init_philo(t_philo *philo, t_table *table);
void	init_mutex(t_table *table);
void	init_all(t_philo *philo, t_table *table, char **argv);

//routine
void	philo_think(t_philo *philo);
bool	forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	routine_philo(t_philo *philo);

#endif