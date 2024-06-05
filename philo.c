/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:45:00 by mbankhar          #+#    #+#             */
/*   Updated: 2024/06/05 16:17:44 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	locked_print(char *str, long long int time, int id, t_philosopher *philosopher, t_diner *diner)
{
	pthread_mutex_lock(&diner->write_lock);
	if (diner->someone_died == 1)
	{
		pthread_mutex_unlock(&diner->write_lock);	
		return ;
	}
	printf("%llu %d %s\n", time, id, str);
	pthread_mutex_unlock(&diner->write_lock);
}

void	init_threads(t_diner *diner, t_philosopher *philosopher)
{
	pthread_t		thread[PHILO_MAX];
	pthread_mutex_t	fork_phil[PHILO_MAX];
	int				i;

	i = -1;
	while (++i < diner->philo_nbr)
		pthread_mutex_init(&fork_phil[i], NULL);
	i = -1;
	while (++i < diner->philo_nbr)
		philosopher[i].forks = fork_phil;
	i = -1;
	while (diner->philo_nbr > ++i)
	{
		(philosopher[i]).philo = &thread[i];
		pthread_create(philosopher[i].philo, NULL, routine, &philosopher[i]);
	}
	monitor_thread(philosopher);
	i = -1;
	while (diner->philo_nbr > ++i)
		pthread_join(*philosopher[i].philo, NULL);
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
	pthread_mutex_lock(&philosopher->forks[left_fork]);
	pthread_mutex_lock(&philosopher->forks[right_fork]);
	time = get_time() - philosopher->start_time;
	if (diner->someone_died == 1)
	{
		pthread_mutex_unlock(&philosopher->forks[right_fork]);
		pthread_mutex_unlock(&philosopher->forks[left_fork]);
		return ;
	}
	locked_print("has taken a fork", time, philosopher->id, philosopher, diner);
	locked_print("has taken a fork", time, philosopher->id, philosopher, diner);
	locked_print("is eating", time, philosopher->id, philosopher, diner);
	ft_usleep(diner->time_to_eat / 1000);
	philosopher->last_meal = get_time();
	pthread_mutex_lock(&diner->meal_lock);
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
	locked_print("is sleeping", time, philosopher->id, philosopher, diner);
	ft_usleep(diner->time_to_sleep / 1000);
}

void	thinking(t_philosopher *philosopher, t_diner *diner)
{
	u_int64_t	time;

	time = get_time() - philosopher->start_time;
	if (diner->someone_died == 1)
		return ;
	locked_print("is thinking", time, philosopher->id, philosopher, diner);
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


// all functions again because this is shit

void	*checkfordead(void *data)
{
	int				i;
	long long		time;
	t_philosopher	*philosopher;
	t_diner			*diner;
	int				checker;

	i = 1;
	philosopher = (t_philosopher *)data;
	diner = philosopher->diner;
	while (1)
	{
		i = -1;
		while (++i < diner->philo_nbr)
		{
			time = get_time() - philosopher[i].last_meal;
			if (time >= diner->time_to_die)
			{
				time = get_time() - philosopher[i].start_time;
				diner->someone_died = 1;
				pthread_mutex_lock(&diner->write_lock);
				printf("%llu %d %s\n", time, philosopher[i].id, "died");
				pthread_mutex_unlock(&diner->write_lock);
				i = -1;
				while (diner->philo_nbr > ++i)
					pthread_join(*philosopher[i].philo, NULL);
				return (NULL);
			}
		}
		i = -1;
		checker = 0;
		while (++i < diner->philo_nbr)
		{
			if (philosopher[i].number_of_meals == diner->nbr_of_cycles)
				checker += 1;
		}
		if (checker == diner->philo_nbr)
			break ;
		usleep(1000);
	}
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
