/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:02:35 by yara              #+#    #+#             */
/*   Updated: 2025/10/01 16:25:22 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
/* # define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define RESET "\x1B[0m" */

struct	s_program;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	size_t				last_meal;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				time_to_die;
	size_t				start_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					meals_eaten;
	struct s_program	*program;
}	t_philo;

typedef struct s_program
{
	int					dead_flag;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		eat_lock;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	int					num_philos;
}	t_program;

typedef struct s_init_args
{
	int		num_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
}	t_init_args;

int		init_program(t_program *program, t_init_args args);
int		init_mutexes(t_program *program);
int		init_forks(t_program *program);
void	init_philo_data(t_philo *philo, int id, t_program *program,
			size_t *times);
size_t	get_time_ms(void);
void	custom_sleep(size_t ms);
void	print_status(t_philo *philo, char *status);
void	philo_eat(t_philo *philo);
void	*philosopher_routine(void *arg);
void	monitor_philosophers(t_program *program, int meals_limit);
int		start_simulation(t_program *program, int meals_limit);
void	cleanup(t_program *program);
int		valid_args(int argc, char **argv);
int		ft_atol(char *str);
int		ft_is_positive_number(char *str);

#endif