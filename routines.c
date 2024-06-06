/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:59:25 by mbankhar          #+#    #+#             */
/*   Updated: 2024/06/06 15:36:55 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating_forks(int right_fork, int left_fork, t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->forks[right_fork]);
	pthread_mutex_lock(&philosopher->forks[left_fork]);
}

void	eating(t_philosopher *philosopher, t_diner *diner)
{
	int			left_fork;
	int			right_fork;
	u_int64_t	time;

	left_fork = philosopher->id - 1;
	right_fork = philosopher->id % diner->philo_nbr;
	if (diner->someone_died == 1)
		return ;
	if (philosopher->id == diner->philo_nbr)
		eating_forks(right_fork, left_fork, philosopher);
	else
		eating_forks(left_fork, right_fork, philosopher);
	time = get_time() - philosopher->start_time;
	locked_print("has taken a fork", time, philosopher->id, diner);
	locked_print("has taken a fork", time, philosopher->id, diner);
	locked_print("is eating", time, philosopher->id, diner);
	ft_usleep(diner->time_to_eat / 1000);
	pthread_mutex_lock(&diner->meal_lock);
	philosopher->last_meal = get_time();
	philosopher->number_of_meals++;
	pthread_mutex_unlock(&diner->meal_lock);
	pthread_mutex_unlock(&philosopher->forks[right_fork]);
	pthread_mutex_unlock(&philosopher->forks[left_fork]);
}

void	sleeping(t_philosopher *philosopher, t_diner *diner)
{
	u_int64_t	time;

	time = get_time() - philosopher->start_time;
	if (diner->someone_died == 1)
		return ;
	locked_print("is sleeping", time, philosopher->id, diner);
	ft_usleep(diner->time_to_sleep / 1000);
}

void	thinking(t_philosopher *philosopher, t_diner *diner)
{
	u_int64_t	time;

	time = get_time() - philosopher->start_time;
	if (diner->someone_died == 1)
		return ;
	locked_print("is thinking", time, philosopher->id, diner);
}

void	*routine(void *data)
{
	t_diner			*diner;
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	diner = philosopher->diner;
	if (philosopher->id % 2 != 0)
		ft_usleep((diner->time_to_eat / 2) / 1000);
	while (42)
	{
		if (diner->philo_nbr == 1)
		{
			usleep(diner->time_to_die);
			break ;
		}
		if (diner->someone_died == 1)
			break ;
		eating(philosopher, diner);
		if (philosopher->number_of_meals == diner->nbr_of_cycles)
			break ;
		sleeping(philosopher, diner);
		thinking(philosopher, diner);
	}
	return (NULL);
}
