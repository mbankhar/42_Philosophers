/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:02:51 by mbankhar          #+#    #+#             */
/*   Updated: 2024/06/08 17:46:32 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atol(const char *str)
{
	int				i;
	long long int	result;

	result = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		error("Minus number");
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		error("Garbage value");
	if (result > INT_MAX)
		error("Max Int");
	return (result);
}

void	check_args(int argc, char **argv, t_diner *diner)
{
	if (argc == 5 || argc == 6)
	{
		diner->philo_nbr = ft_atol(argv[1]);
		diner->time_to_die = ft_atol(argv[2]);
		diner->time_to_eat = ft_atol(argv[3]) * 1000;
		diner->time_to_sleep = ft_atol(argv[4]) * 1000;
		diner->meals = 0;
		diner->someone_died = 0;
		diner->who_died = 0;
		if (argc == 5)
			diner->nbr_of_cycles = -1;
		else if (ft_atol(argv[5]) == 0)
			exit(EXIT_SUCCESS);
		else if (argc == 6)
			diner->nbr_of_cycles = ft_atol(argv[5]);
	}
	else
	{
		write(1, "Arg error", 10);
		exit(EXIT_FAILURE);
	}
}

void	eat_for(int right_fork, int left_fork, t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->forks[right_fork]);
	pthread_mutex_lock(&philosopher->forks[left_fork]);
}

int	one_philo(t_diner *diner, t_philosopher *philosopher)
{
	long long	time;

	if (diner->philo_nbr == 1)
	{
		time = get_time() - philosopher->start_time;
		locked_print("has taken a fork", time, philosopher->id, diner);
		usleep(diner->time_to_die);
		return (0);
	}
	return (1);
}

void	do_shit2(t_diner *diner)
{
	pthread_mutex_unlock(&diner->meal_lock);
	pthread_mutex_lock(&diner->dead_lock);
	diner->someone_died = 1;
	pthread_mutex_unlock(&diner->dead_lock);
}
