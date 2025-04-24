/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:57:18 by david             #+#    #+#             */
/*   Updated: 2025/04/24 11:20:20 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// =============================================================================
// struct s_philo :
//
// id -> identifier un philo
// meals_eaten -> cmb de fois un philo a manger, atteint nbr_times_philo_eat
// last_meal_time -> dernier repas du philo
// thread -> represente un philo
// fork_lock -> verouiller les fourchettes
// state -> etat du philo
// state_lock -> verouiller l'etat du philo
// *table -> la structure philo a acces a la structure table (philo->table)
// *next -> accede a la fourchette suivante
//
// =============================================================================
// struct s_table : simulation globale du programme
//
// nbr_of_philo -> nbr de philo autour de la table
// time_to_die -> temps avant de mourir
// time_to_eat -> temps pour manger
// time_to_sleep -> temps pour dormir
// nbr_meals_eat -> nbr de repas que va manger le philo = option dans args
// start_time -> debut de simulation = temps actuel
// someone_died -> boolean pour la mort
// death_lock -> verouille l'etat de mort
// print_lock -> verouille les print (evite data race)
// philo[MAX_PHILO] -> la structure table a acces a la structure philo
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

typedef struct s_table	t_table;

typedef enum e_philo_state
{
	EAT,
	SLEEP,
	THINK,
	DEAD
}	t_philo_state;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	size_t			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	fork_lock;
	t_philo_state	state;
	pthread_mutex_t	state_lock;
	t_table			*table;
	struct s_philo	*next;
}	t_philo;

typedef struct s_table
{
	int				nbr_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nbr_meals_eat;
	size_t			start_time;
	bool			someone_died;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	print_lock;
	t_philo			philo[MAX_PHILO];
}	t_table;

//utils
int		ft_atoi(const char *str);
void	print_state(t_philo *philo, const char *message);

//time
size_t	current_time(void);
int		ft_usleep(size_t ms);

//init
void	create_threads(t_table *table);
void	wait_for_thread(t_table *table);
void	init_philo(t_table *table);
void	init_table(t_table *table, char **argv);

//forks
bool	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);

//conditions
bool	philo_is_dead(t_philo *philo);
bool	all_philo_have_eat(t_table *table);

//routine
void	philo_think(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_die(t_philo *philo);
void	*routine_philo(void *param);

//main
int		check_args(int argc, char **argv);

#endif
