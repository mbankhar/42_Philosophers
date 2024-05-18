/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:45:00 by mbankhar          #+#    #+#             */
/*   Updated: 2024/05/18 18:44:27 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	check_args(int argc, char **argv)
// {
// 	t_philo	*vari;

// 	if (argc == 5 || argc == 6)
// 	{
// 		vari = malloc(sizeof(struct s_philo));
// 		vari->philo_nbr = argv[1];
// 		vari->time_to_die = argv[2];
// 		vari->time_to_eat = argv[3];
// 		vari->time_to_sleep = argv[4];
// 		if (argc == 6)
// 			vari->nbr_of_cycles = argv[5];
// 	}
// 	else
// 	{
// 		write(1, "Arg error", 10);
// 		exit(EXIT_FAILURE);
// 	}
// }

void	*think(void *data)
{
	printf("This works");
	return (NULL);
}

void	init_threads(void)
{
	t_philo		*vari;
	pthread_t	philo[7];
	int			i;

	vari = malloc(sizeof(t_philo));
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

int	main(int argc, char**argv)
{
	// check_args(argc, argv);
	init_threads();
}
