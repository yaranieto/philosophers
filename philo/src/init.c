/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:41:26 by yara              #+#    #+#             */
/*   Updated: 2025/10/02 13:22:51 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		init_args(t_program *program, int argc, char **argv)
{
	t_init_args	args;

	if (!valid_args(argc, argv))
		ft_error_printing("Invalid args");
	program->num_philos = ft_atol(argv[1]);
	program->time_to_die  = ft_atol(argv[2]);
	program->time_to_die  = ft_atol(argv[3]);
	program->time_to_die  = ft_atol(argv[4]);
	if (argv[5])
		program->num_meals = ft_atol(argv[5]);
	else 
		program->num_meals = -1;
	return (0);
}

void	init_philos(t_philo *philos, t_program *prog, pthread_mutex_t *fork, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philos[i].id = i + 1;
		philos[i].eaters = 0;
		philos[i].meals = 0;
		init_input(&philos[i], av);
		philos[i].start_time = get_time();
		philos[i].last_meal = get_time();
		philos[i].write_lock = &prog->write_lock;
		philos[i].dead_lock = &prog->dead_lock;
		philos[i].meal_lock = &prog->meal_lock;
		philos[i].dead = &prog->dead_flag;
		philos[i].left_fork = &fork[i];
		if (i == 0)
			philos[i].right_fork = &fork[philos[i].num_philosophers - 1];
		else
			philos[i].right_fork = &fork[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->print_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->eat_lock, NULL);
}
