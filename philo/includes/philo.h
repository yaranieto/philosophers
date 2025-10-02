/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:02:35 by yara              #+#    #+#             */
/*   Updated: 2025/10/02 13:21:47 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

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
}	t_philo;

typedef struct s_program
{
	int					dead_flag;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		eat_lock;
	pthread_mutex_t		print_lock;
	t_philo				*philos;
}	t_program;

// Parser functions
int		valid_args(int argc, char **argv);
int		ft_atol(char *str);
int		ft_is_positive_number(char *str);
