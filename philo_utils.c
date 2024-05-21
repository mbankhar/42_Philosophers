/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:20:39 by mbankhar          #+#    #+#             */
/*   Updated: 2024/05/21 15:35:33 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	usleep_busy_wait(useconds_t usec)
// {
// 	struct timeval	start;
// 	struct timeval	end;

// 	gettimeofday(&start, NULL);
// 	do
// 	{
// 		gettimeofday(&end, NULL);
// 	}
// 	while ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec
// 			- start.tv_usec) < usec);
// }

// uint64_t	get_time(void)
// {
// 	struct timeval	tv;

// 	if (gettimeofday(&tv, NULL))
// 		return (0);
// 	return ((tv.tv_sec * (uint64_t)1000) * (tv.tv_usec / 1000));
// }

void	error(char *str)
{
	printf("%s", str);
	exit(EXIT_FAILURE);
}