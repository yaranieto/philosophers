/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:24:47 by yara              #+#    #+#             */
/*   Updated: 2025/10/02 13:33:38 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	thinking(t_philo *philos)
{
	print_routine ("is thinking", philo, philo->id);
}

void	sleeping(t_philo *philos)
{
	print_routine ("is sleeping", philo, philo->id);
	ft_usleep (philo->time_to_sleep);
	return ;
}
// repasar la funcion!!!
void	think(t_philo *philos)
{
	pthread_mutex_lock(philo->right_fork);
	print_routine("has taken a fork", philo, philo->id);
	if (philo->num_philosophers == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_routine("has taken a fork", philo, philo->id);
	philo->eaters = TRUE;
	print_routine("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eaters = FALSE;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return ;
}
}