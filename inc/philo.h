/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:59:31 by david             #+#    #+#             */
/*   Updated: 2025/04/13 12:46:53 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// =============================================================================
// struct s_table : simulation globale du programme
//
// nbr_times_philo_eat -> nbr de repas que va manger le philo
// sim_end -> mettre fin a la simulation (philo mort ou tous manger)
// start_time -> calcule temps ecouler depuis le debut de la simu en ms
// sim_lock -> proteger contre les data races
// forks[MAX_PHILO] -> tableau mutex pour les fourchettes
// print_lock -> eviter que les printf se superpose
//
// =============================================================================
// struct s_philo :
//
// id -> numeroter les philo
// meals_eaten -> cmb de fois un philo a manger, atteint nbr_times_philo_eat
// last_meal_time -> dernier repas de chaque philo
// thread -> represente un philo
// left_fork -> ptr vers fourchette gauche
// right_fork -> ptr vers fourchette droite
// state -> ptr vers les enums
// table -> ptr vers la simu globale
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
	size_t			time_to_die;
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
size_t	current_time(void);
int		ft_usleep(size_t ms);

//error
int		check_args(int argc, char **argv);

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

//condition
bool	check_philo_dead(t_philo *philo);
bool	all_philo_have_eat(t_philo *philo);\
void	monitoring_simulation(t_philo *philo);

#endif