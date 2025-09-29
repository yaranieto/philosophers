/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:11:09 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/09/29 17:13:38 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <pthread.h>
#include <stdio.h>

typedef	struct s_philo
{
	pthread_t	threat;
	int			id;
	size_t		last_meal;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		time_to_die;
	size_t		start_time;
} 	t_philo;

typedef	struct	s_program
{
	int				dead_flag;
	pthreat_mutex_t	dead_lock;
	pthreat_mutex_t	eat_lock;
	t_philo			*philos;
}	t_program;

//parser
int	valid_args(int argc, char **argv);
int	ft_atol(char *str);
int	ft_is_positive_number(char *str);
//long long (o size_t) es para la gestión del tiempo.