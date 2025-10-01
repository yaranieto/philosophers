/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:30:21 by yara              #+#    #+#             */
/*   Updated: 2025/10/01 16:11:33 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_death(t_program *program, int i, size_t current_time)
{
	if ((current_time - program->philos[i].last_meal)
		> program->philos[i].time_to_die)
	{
		pthread_mutex_unlock(&program->eat_lock);
		pthread_mutex_lock(&program->dead_lock);
		program->dead_flag = 1;
		pthread_mutex_unlock(&program->dead_lock);
		printf("%zu %d died\n",
			(current_time - program->philos[i].start_time),
			program->philos[i].id);
		return (1);
	}
	return (0);
}

static int	check_meals(t_program *program, int meals_limit)
{
	int	i;
	int	all_ate;

	i = -1;
	all_ate = 1;
	while (++i < program->num_philos)
	{
		if (meals_limit > 0 && program->philos[i].meals_eaten < meals_limit)
		{
			all_ate = 0;
			break ;
		}
	}
	return (all_ate);
}

void	monitor_philosophers(t_program *program, int meals_limit)
{
	int		i;
	size_t	current_time;

	while (1)
	{
		i = -1;
		while (++i < program->num_philos)
		{
			pthread_mutex_lock(&program->eat_lock);
			current_time = get_time_ms();
			if (check_death(program, i, current_time))
				return ;
			pthread_mutex_unlock(&program->eat_lock);
		}
		if (meals_limit > 0 && check_meals(program, meals_limit))
		{
			pthread_mutex_lock(&program->dead_lock);
			program->dead_flag = 1;
			pthread_mutex_unlock(&program->dead_lock);
			return ;
		}
		usleep(1000);
	}
}
