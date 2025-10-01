/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:30:21 by yara              #+#    #+#             */
/*   Updated: 2025/10/01 16:17:56 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start_simulation(t_program *program, int meals_limit)
{
	int		i;
	size_t	start_time;

	i = 0;
	start_time = get_time_ms();
	while (i < program->num_philos)
	{
		program->philos[i].start_time = start_time;
		program->philos[i].last_meal = start_time;
		program->philos[i].program = program;
		if (pthread_create(&program->philos[i].thread, NULL,
				philosopher_routine, &program->philos[i]) != 0)
			return (1);
		i++;
	}
	monitor_philosophers(program, meals_limit);
	i = 0;
	while (i < program->num_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
