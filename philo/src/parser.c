/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:35:22 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/09/29 14:54:05 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	valid_args(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		printf("%s, Error: invalid arguments/n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (!ft_is_positive_number(argv[i]) | ft_atol(argv[i]) < 0)
		{
			printf ("%s, Error: arguments must be positive numbers/n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_atol(char *str)
{
	long	result;
	int 	i;
	
	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-' )
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result);
}

int	ft_is_positive_number(char *str)
{
	int i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return(0);
	while (str[i])
	{
		if (str[i] < '0' && str[i] > '9')
			return (0);
	}
	return (1);
}
