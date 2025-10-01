/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:03:32 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/10/01 16:11:31 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_from_args(t_program *program, int argc, char **argv)
{
	t_init_args	args;

	if (!valid_args(argc, argv))
		return (1);
	args.num_philos = ft_atol(argv[1]);
	args.time_to_die = ft_atol(argv[2]);
	args.time_to_eat = ft_atol(argv[3]);
	args.time_to_sleep = ft_atol(argv[4]);
	return (init_program(program, args));
}

static int	print_usage(char *prog_name)
{
	printf("Error: invalid number of arguments\n");
	printf("Usage: %s num_philos time_to_die time_to_eat ", prog_name);
	printf("time_to_sleep [num_meals]\n");
	return (1);
}

int	main(int argc, char **argv)
{
	t_program	program;
	int			meals_limit;

	meals_limit = -1;
	if (argc < 5 || argc > 6)
		return (print_usage(argv[0]));
	if (init_from_args(&program, argc, argv) != 0)
	{
		printf("Error: initialization failed\n");
		return (1);
	}
	if (argc == 6)
		meals_limit = ft_atol(argv[5]);
	if (start_simulation(&program, meals_limit) != 0)
	{
		printf("Error: simulation failed\n");
		cleanup(&program);
		return (1);
	}
	cleanup(&program);
	return (0);
}
