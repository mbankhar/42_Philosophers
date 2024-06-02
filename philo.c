/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:45:00 by mbankhar          #+#    #+#             */
/*   Updated: 2024/06/02 18:18:35 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (u_int64_t)(1000)) + (tv.tv_usec / 1000));
}

void	usleep_busy_wait(useconds_t usec)
{
	struct timeval	start;
	struct timeval	end;
	long long		time;

	gettimeofday(&start, NULL);

	while ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec
			- start.tv_usec) < usec);
}

int	 ft_usleep(unsigned int time, t_philosopher *philosopher, t_diner *diner)
{
	long int		start;

	start = get_time();
	while (get_time() - start < time)
	{
		usleep(100);
		pthread_mutex_lock(&diner->meal_lock);
			time = get_time() - philosopher->last_meal;
			pthread_mutex_unlock(&diner->meal_lock);
			if (time >= diner->time_to_die)
			{
				time = get_time() - philosopher->start_time;
				pthread_mutex_lock(&diner->write_lock);
				printf("FUKTHISSHIT%u %d died\n", time, philosopher->id);
				pthread_mutex_unlock(&diner->write_lock);
				exit(1);
			}
	return (0);
	}
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
	pthread_mutex_init(&diner->start_mutex, NULL);
	diner->created_threads = 0;
	while (diner->philo_nbr > ++i)
	{
		(philosopher[i]).philo = &thread[i];
		pthread_create(philosopher[i].philo, NULL, routine, &philosopher[i]);
	}
	monitor_thread(philosopher);
	i = -1;
	while (diner->philo_nbr > ++i)
		pthread_join(*philosopher[i].philo, NULL);
	pthread_mutex_destroy(&diner->start_mutex);
}

void	init_philos(t_diner *diner, t_philosopher *philosopher)
{
	int	i;

	i = -1;
	while (++i < diner->philo_nbr)
	{
		philosopher[i].id = i + 1;
		philosopher[i].last_meal = 0;
		philosopher[i].is_dead = 0;
		philosopher[i].number_of_meals = 0;
		philosopher[i].diner = diner;
		philosopher[i].start_time = get_time();
		philosopher[i].last_meal = get_time();
		philosopher[i].write_lock = diner->write_lock;
		philosopher[i].dead_lock = diner->dead_lock;
		philosopher[i].meal_lock = diner->meal_lock;
	}
}


void	eating(t_philosopher *philosopher, t_diner *diner)
{
	int			left_fork;
	int			right_fork;
	u_int64_t	time;

	left_fork = philosopher->id - 1;
	right_fork = philosopher->id % diner->philo_nbr;
	if (philosopher->id % 2 == 0)
	{
		pthread_mutex_lock(&philosopher->forks[left_fork]);
		pthread_mutex_lock(&philosopher->forks[right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philosopher->forks[right_fork]);
		pthread_mutex_lock(&philosopher->forks[left_fork]);
	}
	// pthread_mutex_lock(&philosopher->forks[left_fork]);
	// pthread_mutex_lock(&philosopher->forks[right_fork]);
	pthread_mutex_lock(&diner->write_lock);
	time = get_time() - philosopher->start_time;
	printf("%llu %d has taken a fork\n", time, philosopher->id);
	printf("%llu %d has taken a fork\n", time, philosopher->id);
	printf("%llu %d is eating\n", time, philosopher->id);
	pthread_mutex_unlock(&diner->write_lock);
	// usleep_busy_wait(diner->time_to_eat, philosopher, diner);
	ft_usleep(diner->time_to_eat, philosopher, diner);
	pthread_mutex_lock(&philosopher->meal_lock);
	philosopher->last_meal = get_time();
	philosopher->number_of_meals++;
	pthread_mutex_unlock(&philosopher->meal_lock);
	pthread_mutex_unlock(&philosopher->forks[right_fork]);
	pthread_mutex_unlock(&philosopher->forks[left_fork]);
}

void	sleeping(t_philosopher *philosopher, t_diner *diner)
{
	u_int64_t	time;

	pthread_mutex_lock(&diner->write_lock);
	time = get_time() - philosopher->start_time;
	printf("%llu %d is sleeping\n", time, philosopher->id);
	pthread_mutex_unlock(&diner->write_lock);
	// usleep_busy_wait(diner->time_to_sleep, philosopher, diner);
	ft_usleep(diner->time_to_sleep, philosopher, diner);
}

void	thinking(t_philosopher *philosopher, t_diner *diner)
{
	u_int64_t	time;

	pthread_mutex_lock(&diner->write_lock);
	time = get_time() - philosopher->start_time;
	printf("%llu %d is thinking\n", time, philosopher->id);
	pthread_mutex_unlock(&diner->write_lock);
}

void	*routine(void *data)
{
	t_diner			*diner;
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	diner = philosopher->diner;
	if (philosopher->id % 2 != 0)
		usleep_busy_wait(diner->time_to_eat / 2);
	while (42)
	{
		eating(philosopher, diner);
		if (philosopher->number_of_meals == diner->nbr_of_cycles)
			break ;
		sleeping(philosopher, diner);
		thinking(philosopher, diner);
		if (philosopher->number_of_meals == diner->nbr_of_cycles)
			break ;
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

	i = 1;
	philosopher = (t_philosopher *)data;
	diner = philosopher->diner;
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
				time = get_time() - philosopher[i].start_time;
				pthread_mutex_lock(&diner->write_lock);
				printf("%llu %d died\n", time, philosopher[i].id);
				pthread_mutex_unlock(&diner->write_lock);
				while (++i < diner->philo_nbr)
					pthread_mutex_unlock(&philosopher->forks[i]);
				exit(1);
				return (NULL);
			}
		}
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
	pthread_mutex_init(&diner.dead_lock, NULL);
	pthread_mutex_init(&diner.meal_lock, NULL);
	init_philos(&diner, philosopher);
	init_threads(&diner, philosopher);
	pthread_mutex_destroy(&diner.dead_lock);
	pthread_mutex_destroy(&diner.meal_lock);
	pthread_mutex_destroy(&diner.write_lock);
}
