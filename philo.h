/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:45:10 by mbankhar          #+#    #+#             */
/*   Updated: 2024/05/21 17:01:21 by mbankhar         ###   ########.fr       */
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
# include <time.h>
# include <errno.h>
# include <limits.h>

typedef struct s_philosopher
{
	
	t_diner	*t_diner;
}	t_philosopher;

typedef struct s_diner
{
	int	philo_nbr;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_of_cycles;
}		t_diner;

int			ft_atol(const char *str);
void		check_args(int argc, char **argv, t_diner **vari);
void		usleep_busy_wait(useconds_t usec);
uint64_t	get_time(void);
void		error(char *str);

#endif