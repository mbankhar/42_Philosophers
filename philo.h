/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:45:10 by mbankhar          #+#    #+#             */
/*   Updated: 2024/05/30 16:57:37 by mbankhar         ###   ########.fr       */
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
# include <sys/time.h>
# define PHILO_MAX 200

struct	s_diner;
struct	s_philosopher;

typedef struct s_philosopher
{
	int				id;
	long			last_meal;
	int				is_dead;
	long			number_of_meals;
	pthread_t		*philo;
	pthread_mutex_t	*forks;
	struct s_diner	*t_diner;
}	t_philosopher;

typedef struct s_diner
{
	int				dead_flag;
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_cycles;
	int				count;
	pthread_mutex_t start_mutex; // Add a start mutex
    int created_threads; // Add a counter for created threads
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philosopher	*philo;
}		t_diner;


int			ft_atol(const char *str);
void		check_args(int argc, char **argv, t_diner *diner);
void		usleep_busy_wait(useconds_t usec);
uint64_t	get_time(void);
void		error(char *str);

#endif