/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:30:21 by yara              #+#    #+#             */
/*   Updated: 2025/10/01 17:36:11 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	take_forks(t_philo *philo)
{
	size_t current_time;
	size_t time_since_meal;

	// Dynamic fork taking strategy
	pthread_mutex_lock(&philo->program->eat_lock);
	current_time = get_time_ms();
	time_since_meal = current_time - philo->last_meal;
	pthread_mutex_unlock(&philo->program->eat_lock);
	
	// Priority-based fork acquisition
	if (time_since_meal > (philo->time_to_die * 4) / 5 || philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		// Quick check if second fork is available
		if (pthread_mutex_trylock(philo->right_fork) != 0)
		{
			// Release and retry other order if failed
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(philo->left_fork);
		}
		print_status(philo, "has taken a fork");
	}
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_eat(t_philo *philo)
{
	size_t current_time;
	size_t time_since_meal;
	size_t phase_time;
	size_t phase_size;
	
	pthread_mutex_lock(&philo->program->eat_lock);
	current_time = get_time_ms();
	time_since_meal = current_time - philo->last_meal;
	
	// Emergency priority - if philosopher is close to death
	if (time_since_meal > (philo->time_to_die * 4) / 5)
	{
		pthread_mutex_unlock(&philo->program->eat_lock);
		return;
	}
	
	// Phase-based eating system
	if (philo->program->num_philos > 100)
	{
		// For large groups, use 4 phases
		phase_size = philo->program->num_philos / 4;
		phase_time = (current_time / 50) % 4; // Switch phase every 50ms
		
		// If not in this philosopher's phase and not hungry
		if (time_since_meal < (philo->time_to_die / 2) && 
			(philo->id / phase_size) != phase_time)
		{
			// Small stagger within phase
			usleep((philo->id % 5) * 500);
		}
	}
	else
	{
		// For smaller groups, use 2 phases
		if (time_since_meal < (philo->time_to_die / 2) && 
			((int)(current_time / 30) % 2) != (philo->id % 2))
		{
			// Minimal stagger
			usleep((philo->id % 3) * 300);
		}
	}
	
	pthread_mutex_unlock(&philo->program->eat_lock);
	
	take_forks(philo);
	pthread_mutex_lock(&philo->program->eat_lock);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->program->eat_lock);
	print_status(philo, "is eating");
	custom_sleep(philo->time_to_eat);
	philo->meals_eaten++;
	release_forks(philo);
}
