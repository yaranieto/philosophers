/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:37:01 by yara              #+#    #+#             */
/*   Updated: 2025/10/01 16:11:29 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_philos(t_program *program, size_t *times)
{
	int	i;

	program->philos = malloc(sizeof(t_philo) * program->num_philos);
	if (!program->philos)
		return (1);
	i = 0;
	while (i < program->num_philos)
	{
		init_philo_data(&program->philos[i], i, program, times);
		i++;
	}
	return (0);
}

static int	validate_args(t_init_args args)
{
	if (args.num_philos > 200)
	{
		printf("Error: Too many philosophers (max 200)\n");
		return (1);
	}
	if (args.time_to_die < 60)
	{
		printf("Error: time_to_die too short (min 60ms)\n");
		return (1);
	}
	if (args.time_to_eat < 60 || args.time_to_sleep < 60)
	{
		printf("Error: time_to_eat/sleep too short (min 60ms)\n");
		return (1);
	}
	return (0);
}

static int	init_resources(t_program *program)
{
	if (init_mutexes(program))
	{
		printf("Error: Failed to initialize mutexes\n");
		return (1);
	}
	if (init_forks(program))
	{
		printf("Error: Failed to initialize forks\n");
		cleanup(program);
		return (1);
	}
	return (0);
}

int	init_program(t_program *program, t_init_args args)
{
	size_t	times[3];

	if (validate_args(args))
		return (1);
	program->num_philos = args.num_philos;
	program->dead_flag = 0;
	times[0] = args.time_to_die;
	times[1] = args.time_to_eat;
	times[2] = args.time_to_sleep;
	if (init_resources(program))
		return (1);
	if (init_philos(program, times))
	{
		printf("Error: Failed to initialize philosophers\n");
		cleanup(program);
		return (1);
	}
	return (0);
}
