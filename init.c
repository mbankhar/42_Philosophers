/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:56:56 by mbankhar          #+#    #+#             */
/*   Updated: 2024/06/06 17:45:51 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (diner->philo_nbr > ++i)
	{
		(philosopher[i]).philo = &thread[i];
		pthread_create(philosopher[i].philo, NULL, routine, &philosopher[i]);
	}
	monitor_thread(philosopher);
	i = -1;
	while (diner->philo_nbr > ++i)
		pthread_join(*philosopher[i].philo, NULL);
	i = -1;
	while (++i < diner->philo_nbr)
		pthread_mutex_destroy(&fork_phil[i]);
}
