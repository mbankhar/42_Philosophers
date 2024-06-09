/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:45:10 by mbankhar          #+#    #+#             */
/*   Updated: 2024/06/08 17:47:07 by mbankhar         ###   ########.fr       */
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

typedef struct s_diner	t_diner;
struct					s_philosopher;

typedef struct s_philosopher
{
	int				id;
	long			last_meal;
	u_int64_t		start_time;
	int				is_dead;
	long			number_of_meals;
	pthread_t		*philo;
	pthread_mutex_t	*forks;
	t_diner			*diner;
}	t_philosopher;

typedef struct s_diner
{
	int				who_died;
	int				someone_died;
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_cycles;
	int				meals;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	t_philosopher	*philo;
}		t_diner;

int			ft_atol(const char *str);
void		check_args(int argc, char **argv, t_diner *diner);
int			ft_usleep(unsigned int time_in_microseconds);
u_int64_t	get_time(void);
void		error(char *str);
u_int64_t	get_time(void);
void		init_threads(t_diner *diner, t_philosopher *philosopher);
void		init_philos(t_diner *diner, t_philosopher *philosopher);
void		*routine(void *data);
void		eating(t_philosopher *philosopher, t_diner *diner);
void		sleeping(t_philosopher *philosopher, t_diner *diner);
void		thinking(t_philosopher *philosopher, t_diner *diner);
void		monitor_thread(t_philosopher *philosopher);
void		*routine(void *data);
void		locked_print(char *str, long long int time, int id, t_diner *diner);
void		locked_pr(char *str, long long int time, int id, t_diner *diner);
void		eat_for(int right_fork, int left_fork, t_philosopher *philosopher);
int			one_philo(t_diner *diner, t_philosopher *philosopher);
void		do_shit2(t_diner *diner);

#endif