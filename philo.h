/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:45:10 by mbankhar          #+#    #+#             */
/*   Updated: 2024/05/18 16:34:31 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
	int	philo_nbr;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_of_cycles;
}		t_philo;

#endif