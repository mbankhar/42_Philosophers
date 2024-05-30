/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:45:00 by mbankhar          #+#    #+#             */
/*   Updated: 2024/05/30 17:16:48 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	print_microseconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000LL + tv.tv_usec);
}

void	*routine(void *data)
{
	t_diner			*diner;
	t_philosopher	*philosopher;
	int				left_fork;
	int				right_fork;

	philosopher = (t_philosopher *)data;
	diner = philosopher->t_diner;
	left_fork = philosopher->id;
	right_fork = (philosopher->id + 1) % diner->philo_nbr;
	pthread_mutex_lock(&diner->start_mutex);
	diner->created_threads++;
	while (diner->created_threads < diner->philo_nbr)
	{
		pthread_mutex_unlock(&diner->start_mutex);
		usleep(100);
		pthread_mutex_lock(&diner->start_mutex);
	}
	pthread_mutex_unlock(&diner->start_mutex);
	if (philosopher->id % 2 == 0)
		usleep(10);
	// printf("%lld\n", print_microseconds());
	printf("%d", left_fork);
	printf("%d\n", right_fork);
	// pthread_mutex_lock(&philosopher->forks[philosopher->id]);
	// printf("%d\n", diner->philo_nbr);
	// printf("%d\n", philosopher->id);
	// pthread_mutex_unlock(&philosopher->forks[philosopher->id]);
	// while (!dead_check || !eat_enough)
	// {
	// 	eating(philosopher, diner);
	// 	sleeping(philosopher, diner);
	// 	thinking(philosopher, diner);
	// }
	return (NULL);
}

void	init_threads(t_diner *diner, t_philosopher *philosopher)
{
	pthread_t		thread[PHILO_MAX];
	pthread_mutex_t	fork_phil[PHILO_MAX];
	int				i;

	i = -1;
	while (diner->philo_nbr > ++i)
	{
		(philosopher[i]).forks = fork_phil;
		pthread_mutex_init(philosopher[i].forks, NULL);
	}
	i = -1;
	pthread_mutex_init(&diner->start_mutex, NULL);
	diner->created_threads = 0;
	while (diner->philo_nbr > ++i)
	{
		usleep(5);
		(philosopher[i]).philo = &thread[i];
		pthread_create(philosopher[i].philo, NULL, routine, &philosopher[i]);
	}
	i = -1;
	while (diner->philo_nbr > ++i)
	{
		pthread_join(*philosopher[i].philo, NULL);
	}
	// pthread_mutex_destroy(&diner->start_mutex);
	// pthread_cond_destroy(&diner->start_cond);
}

void	init_philos(t_diner *diner, t_philosopher *philosopher)
{
	int	i;

	i = -1;
	while (++i < diner->philo_nbr)
	{
		philosopher[i].id = i;
		philosopher[i].last_meal = 0;
		philosopher[i].is_dead = 0;
		philosopher[i].number_of_meals = 0;
		philosopher[i].t_diner = diner;
	}
}

int	main(int argc, char **argv)
{
	t_diner			diner;
	t_philosopher	philosopher[PHILO_MAX];	

	check_args(argc, argv, &diner);
	diner.philo = philosopher;
	pthread_mutex_init(&diner.write_lock, NULL);
	pthread_mutex_init(&diner.dead_lock, NULL);
	pthread_mutex_init(&diner.meal_lock, NULL);
	init_philos(&diner, philosopher);
	init_threads(&diner, philosopher);
}
