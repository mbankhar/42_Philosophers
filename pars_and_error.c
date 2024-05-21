/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:02:51 by mbankhar          #+#    #+#             */
/*   Updated: 2024/05/21 15:58:40 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atol(const char *str)
{
	int				i;
	long long int	result;

	result = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		error("Minus number");
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		error("Garbage value");
	if (result > INT_MAX)
		error("Max Int");
	return (result);
}

void	check_args(int argc, char **argv, t_diner **vari)
{
	if (argc == 5 || argc == 6)
	{
		*vari = malloc(sizeof(struct s_diner));
		if (!vari)
			error("Allocation failed");
		(*vari)->philo_nbr = ft_atol(argv[1]);
		(*vari)->time_to_die = ft_atol(argv[2]) * 1000;
		(*vari)->time_to_eat = ft_atol(argv[3]) * 1000;
		(*vari)->time_to_sleep = ft_atol(argv[4]) * 1000;
		if (argc == 6)
			(*vari)->nbr_of_cycles = ft_atol(argv[5]);
	}
	else
	{
		write(1, "Arg error", 10);
		exit(EXIT_FAILURE);
	}
}
