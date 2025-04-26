/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:57:49 by david             #+#    #+#             */
/*   Updated: 2025/04/26 15:14:08 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			sign = -sign;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

void	print_state(t_philo *philo, const char *state)
{
	if (is_program_running(philo->table) == false)
		return ;
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%lu Philosopher %d %s\n", current_time() - philo->table->start_time,
		philo->id, state);
	pthread_mutex_unlock(&philo->table->print_lock);
}

bool	is_program_running(t_table *table)
{
	bool	running;

	pthread_mutex_lock(&table->death_lock);
	running = table->program_run;
	pthread_mutex_unlock(&table->death_lock);
	return (running);
}
