/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:45:00 by mbankhar          #+#    #+#             */
/*   Updated: 2024/06/05 19:16:55 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_for_eating(t_diner *diner, t_philosopher *philosopher)
{
	int	i;
	int	checker;

	i = -1;
	checker = 0;
	while (++i < diner->philo_nbr)
	{
		pthread_mutex_lock(&diner->meal_lock);
		if (philosopher[i].number_of_meals == diner->nbr_of_cycles)
			checker += 1;
		pthread_mutex_unlock(&diner->meal_lock);
	}
	if (checker == diner->philo_nbr)
		return (0);
	return (1);
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
				pthread_mutex_lock(&diner->meal_lock);
				time = get_time() - philosopher[i].start_time;
				pthread_mutex_unlock(&diner->meal_lock);
				diner->someone_died = 1;
				pthread_mutex_lock(&diner->write_lock);
				printf("%llu %d %s\n", time, philosopher[i].id, "died");
				pthread_mutex_unlock(&diner->write_lock);
				return (0);
			}
		}
		if (check_for_eating(diner, philosopher) == 0)
			break ;
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
	i = 0;
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
	t_diner			*diner;

	diner = philosopher->diner;
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
	init_philos(&diner, philosopher);
	init_threads(&diner, philosopher);
	pthread_mutex_destroy(&diner.meal_lock);
	pthread_mutex_destroy(&diner.write_lock);
}
