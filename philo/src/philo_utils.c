/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:30:21 by yara              #+#    #+#             */
/*   Updated: 2025/10/01 16:18:06 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_philo *philo, char *status)
{
	size_t	current_time;
	int		dead;

	pthread_mutex_lock(&philo->program->dead_lock);
	dead = philo->program->dead_flag;
	pthread_mutex_unlock(&philo->program->dead_lock);
	if (!dead)
	{
		current_time = get_time_ms();
		printf("%zu %d %s\n",
			(current_time - philo->start_time), philo->id, status);
	}
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	custom_sleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

size_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	custom_sleep(size_t ms)
{
	size_t	end_time;

	end_time = get_time_ms() + ms;
	while (get_time_ms() < end_time)
		usleep(100);
}
