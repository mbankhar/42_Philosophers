/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:59:25 by mbankhar          #+#    #+#             */
/*   Updated: 2024/06/08 17:43:29 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_flag_check(t_diner *diner)
{
	pthread_mutex_lock(&diner->dead_lock);
	if (diner->someone_died == 1)
	{
		pthread_mutex_unlock(&diner->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(&diner->dead_lock);
	return (1);
}

void	eating(t_philosopher *philosopher, t_diner *diner)
{
	int			left_fork;
	int			right_fork;
	u_int64_t	time;

	left_fork = philosopher->id - 1;
	right_fork = philosopher->id % diner->philo_nbr;
	if (dead_flag_check(diner) == 0)
		return ;
	eat_for(left_fork, right_fork, philosopher);
	time = get_time() - philosopher->start_time;
	locked_print("has taken a fork", time, philosopher->id, diner);
	locked_print("has taken a fork", time, philosopher->id, diner);
	locked_print("is eating", time, philosopher->id, diner);
	ft_usleep(diner->time_to_eat / 1000);
	pthread_mutex_lock(&diner->meal_lock);
	philosopher->last_meal = get_time();
	philosopher->number_of_meals++;
	diner->meals += 1;
	pthread_mutex_unlock(&diner->meal_lock);
	pthread_mutex_unlock(&philosopher->forks[left_fork]);
	pthread_mutex_unlock(&philosopher->forks[right_fork]);
}

void	sleeping(t_philosopher *philosopher, t_diner *diner)
{
	u_int64_t	time;

	time = get_time() - philosopher->start_time;
	pthread_mutex_lock(&diner->dead_lock);
	if (diner->someone_died == 1)
	{
		pthread_mutex_unlock(&diner->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&diner->dead_lock);
	locked_print("is sleeping", time, philosopher->id, diner);
	ft_usleep(diner->time_to_sleep / 1000);
}

void	thinking(t_philosopher *philosopher, t_diner *diner)
{
	u_int64_t	time;

	time = get_time() - philosopher->start_time;
	pthread_mutex_lock(&diner->dead_lock);
	if (diner->someone_died == 1)
	{
		pthread_mutex_unlock(&diner->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&diner->dead_lock);
	locked_print("is thinking", time, philosopher->id, diner);
}

void	*routine(void *data)
{
	t_diner			*diner;
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	diner = philosopher->diner;
	thinking(philosopher, diner);
	if (philosopher->id % 2 == 0)
		ft_usleep((diner->time_to_eat / 2) / 1000);
	while (42)
	{
		if (one_philo(diner, philosopher) == 0)
			break ;
		if (dead_flag_check(diner) == 0)
			break ;
		eating(philosopher, diner);
		sleeping(philosopher, diner);
		thinking(philosopher, diner);
		if (philosopher->number_of_meals == diner->nbr_of_cycles)
			break ;
	}
	return (NULL);
}
