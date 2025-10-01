/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:45:21 by yara              #+#    #+#             */
/*   Updated: 2025/10/01 16:18:09 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*single_philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->start_time = get_time_ms();
	philo->last_meal = philo->start_time;
	print_status(philo, "has taken a fork");
	custom_sleep(philo->time_to_die);
	print_status(philo, "died");
	pthread_mutex_lock(&philo->program->dead_lock);
	philo->program->dead_flag = 1;
	pthread_mutex_unlock(&philo->program->dead_lock);
	return (NULL);
}

static void	init_philosopher(t_philo *philo)
{
	size_t phase;
	
	philo->start_time = get_time_ms();
	philo->last_meal = philo->start_time;
	
	// Phase-based initialization
	if (philo->program->num_philos > 100)
	{
		// Initialize in phases for large groups
		phase = philo->id / (philo->program->num_philos / 4);
		usleep(phase * 100);
	}
	else if (philo->id % 2 == 1)
	{
		// Small stagger for odd philosophers
		usleep(200);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	int		is_dead;

	philo = (t_philo *)arg;
	if (philo->program->num_philos == 1)
		return (single_philosopher_routine(arg));
	init_philosopher(philo);
	while (1)
	{
		pthread_mutex_lock(&philo->program->dead_lock);
		is_dead = philo->program->dead_flag;
		pthread_mutex_unlock(&philo->program->dead_lock);
		if (is_dead == 1)
			break ;
		philo_eat(philo);
		print_status(philo, "is sleeping");
		custom_sleep(philo->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
