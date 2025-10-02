/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:03:32 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/10/02 12:51:48 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

void	destroy_threads(char *st, t_program, pthread_mutex_t *fork)
{
	int	a;

	a = 0;
	if (str)
	{
		ft_error_print(str);
		ft_error_print("\n");
	}
	pthread_mutex_destroy(&progam-dead_lock);
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	while (a < program->philos[0].num_philosophers)
	{
		pthread_mutex_destroy(&fork[a]);
		a++;
	}
}

int	check_nbr_args(char **argv)
{
	if (ft_atol(argv[1]) <= 0 || ft_is_positive_number (argv[1]))
		return (ft_error_printing("Invalid number of philosophers"));
	if (ft_atol(argv[2]) <= 0 || ft_is_positive_number (argv[2]))
		return (ft_error_printing("Invalid time to die"));
	if (ft_atol(argv[3]) <= 0 || ft_is_positive_number (argv[3]))
		return (ft_error_printing("Invalid time to eat"));
	if (ft_atol(argv[4]) <= 0 || ft_is_positive_number(argv[4]) == 1)
		return (ft_error_printing("Invalid sleep time\n"));
	if (argv[5] && (ft_atol(argv[5]) < 0 || ft_is_positive_number(argv[5]) == 1))
		return (ft_error_printing("Invalid meals\n"));
}