/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:37:01 by yara              #+#    #+#             */
/*   Updated: 2025/10/01 16:11:35 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutexes(t_program *program)
{
	if (pthread_mutex_init(&program->dead_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&program->eat_lock, NULL) != 0)
		return (1);
	return (0);
}

int	init_forks(t_program *program)
{
	int	i;

	program->forks = malloc(sizeof(pthread_mutex_t) * program->num_philos);
	if (!program->forks)
		return (1);
	i = 0;
	while (i < program->num_philos)
	{
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	init_philo_data(t_philo *philo, int id, t_program *program,
		size_t *times)
{
	philo->id = id + 1;
	philo->meals_eaten = 0;
	philo->time_to_die = times[0];
	philo->time_to_eat = times[1];
	philo->time_to_sleep = times[2];
	philo->last_meal = 0;
	philo->start_time = 0;
	philo->left_fork = &program->forks[id];
	philo->right_fork = &program->forks[(id + 1) % program->num_philos];
}
