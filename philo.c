/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:45:00 by mbankhar          #+#    #+#             */
/*   Updated: 2024/05/21 17:11:02 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



pthread_mutex_t	think_lock = PTHREAD_MUTEX_INITIALIZER;

void	*think(void *data)
{
	pthread_mutex_lock(&think_lock);
	pthread_mutex_unlock(&think_lock);
	return (NULL);
}

void	init_threads(t_diner *vari)
{
	pthread_t	*philo;
	int			i;

	philo = malloc(sizeof(pthread_t) * vari->philo_nbr);
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

void	init_philos(t_diner *vari, t_philosopher **inf)
{
	int	i;

	*inf = malloc(sizeof(struct s_philosopher));
		if (!inf)
			error("Allocation failed");
	i = -1;
	while (++i < vari->philo_nbr)
	{
		vari[i].time_to_die = 
	}

}


int	main(int argc, char **argv)
{
	t_diner			*vari;
	t_philosopher	*inf;

	check_args(argc, argv, &vari);
	printf("%d\n", vari->philo_nbr);
	printf("%d\n", vari->time_to_die);
	printf("%d\n", vari->time_to_eat);
	printf("%d\n", vari->time_to_sleep);
	printf("%d\n", vari->nbr_of_cycles);
	init_philos(vari, inf);
	init_threads(vari);
}
