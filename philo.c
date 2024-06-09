/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:45:00 by mbankhar          #+#    #+#             */
/*   Updated: 2024/06/08 17:49:34 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_shit(int i, t_diner *diner, t_philosopher *philosopher)
{
	long long	time;

	pthread_mutex_lock(&diner->meal_lock);
	time = get_time() - philosopher[i].start_time;
	pthread_mutex_unlock(&diner->meal_lock);
	pthread_mutex_lock(&diner->dead_lock);
	diner->someone_died = 1;
	pthread_mutex_unlock(&diner->dead_lock);
	locked_pr("died", time, philosopher[i].id, diner);
}

int	exec(t_diner *diner, t_philosopher *philosopher, long long time, int i)
{
	while (1)
	{
		i = -1;
		while (++i < diner->philo_nbr)
		{
			pthread_mutex_lock(&diner->meal_lock);
			time = get_time() - philosopher[i].last_meal;
			pthread_mutex_unlock(&diner->meal_lock);
			if (time >= diner->time_to_die)
			{
				do_shit(i, diner, philosopher);
				return (0);
			}
		}
		pthread_mutex_lock(&diner->meal_lock);
		if (diner->nbr_of_cycles != -1 && diner->meals
			>= diner->nbr_of_cycles * diner->philo_nbr)
		{
			do_shit2(diner);
			break ;
		}
		pthread_mutex_unlock(&diner->meal_lock);
		usleep(1000);
	}
	return (0);
}

void	*checkfordead(void *data)
{
	int				i;
	long long		time;
	t_philosopher	*philosopher;
	t_diner			*diner;

	time = 0;
	i = -1;
	philosopher = (t_philosopher *)data;
	diner = philosopher->diner;
	if (exec(diner, philosopher, time, i) == 0)
		return (NULL);
	return (NULL);
}

void	monitor_thread(t_philosopher *philosopher)
{
	pthread_t		monitor;
	pthread_mutex_t	monitor_mutex;

	pthread_mutex_init(&monitor_mutex, NULL);
	pthread_create(&monitor, NULL, checkfordead, philosopher);
	pthread_join(monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_diner			diner;
	t_philosopher	philosopher[PHILO_MAX];

	check_args(argc, argv, &diner);
	philosopher->diner = &diner;
	pthread_mutex_init(&diner.write_lock, NULL);
	pthread_mutex_init(&diner.meal_lock, NULL);
	pthread_mutex_init(&diner.dead_lock, NULL);
	init_philos(&diner, philosopher);
	init_threads(&diner, philosopher);
	pthread_mutex_destroy(&diner.meal_lock);
	pthread_mutex_destroy(&diner.write_lock);
	pthread_mutex_destroy(&diner.dead_lock);
}
