/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:45:00 by mbankhar          #+#    #+#             */
/*   Updated: 2024/05/20 11:42:57 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atol(const char *str)
{
	int				i;
	int				sign;
	long long int	result;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

void	check_args(int argc, char **argv)
{
	t_philo	*vari;

	if (argc == 5 || argc == 6)
	{
		vari = malloc(sizeof(struct s_philo));
		vari->philo_nbr = ft_atol(argv[1]);
		vari->time_to_die = ft_atol(argv[2]);
		vari->time_to_eat = ft_atol(argv[3]);
		vari->time_to_sleep = ft_atol(argv[4]);
		if (argc == 6)
			vari->nbr_of_cycles = ft_atol(argv[5]);
	}
	else
	{
		write(1, "Arg error", 10);
		exit(EXIT_FAILURE);
	}
}

int	global_coffe;
pthread_mutex_t	think_lock = PTHREAD_MUTEX_INITIALIZER;

void	*think(void *data)
{
	pthread_mutex_lock(&think_lock);
	printf("This works\n");
	global_coffe += 1;
	printf("%d\n", global_coffe);
	pthread_mutex_unlock(&think_lock);
	return (NULL);
}

void	init_threads(void)
{
	t_philo		*vari;
	pthread_t	philo[6];
	int			i;

	// vari = malloc(sizeof(t_philo));
	i = -1;
	vari->philo_nbr = 5;
	while (vari->philo_nbr > ++i)
	{
		pthread_create(philo + i, NULL, think, NULL);
	}
	i = -1;
	while (vari->philo_nbr > ++i)
	{
		pthread_join(philo[i], NULL);
	}
}

int	main(int argc, char**argv)
{
	check_args(argc, argv);
	init_threads();
}
