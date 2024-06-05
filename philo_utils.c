/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:20:39 by mbankhar          #+#    #+#             */
/*   Updated: 2024/06/05 18:46:49 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *str)
{
	printf("%s", str);
	exit(EXIT_FAILURE);
}

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (u_int64_t)(1000)) + (tv.tv_usec / 1000));
}

int	ft_usleep(unsigned int time_in_microseconds)
{
	long int	start;

	start = get_time();
	while (get_time() - start < time_in_microseconds)
		usleep(100);
	return (0);
}

void	locked_print(char *str, long long int time, int id, t_diner *diner)
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
