/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yara <yara@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:55:30 by yara              #+#    #+#             */
/*   Updated: 2025/10/02 13:28:33 by yara             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_error_printing(char *str)
{
	printf ("%s", str);
	exit (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	get_time(void)
{
	struct	timeval	time; /* Estructura tiempo */
	if (gettimeofday(&time, NULL == -1))/* Comprueba error*/
		ft_error_printing("Error getting time of day");
	return (time.tv_sec *1000 + time.tv_usec / 1000);
}
/* segundos enteros desde Epoch (1 Jan 1970), lo pasa a ms */
/* microsegundos (0 a 999999) dentro del segundo, lo pasa a ms */

void	ft_usleep(size_t ms) /* Recibe ms a "dormir" */
{
	size_t	start;   /* Variable para guardar inicio*/

	start = get_time();  /* Guarda tiempo inicial en ms */
	while((get_time() - start) < ms)
		usleep(500);  /* Duerme SOLO 0.5 ms al final*/
}

/* guarda el tiempo actual en ms y lo resta por el inicio
mientras sea menor a ls ms de la función sigue dormido */

void	print_philos_routine(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start_time;
	if (!dead_loop(philo))
		printf ("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock (philo->write_lock);
	return ;
}