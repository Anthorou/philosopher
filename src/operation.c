/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:05:14 by aroussea          #+#    #+#             */
/*   Updated: 2023/09/28 10:59:48 by aroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat(t_philo *philo)
{
	uint64_t	time;

	pthread_mutex_lock(philo->fork_left);
	message(philo->s_time, philo->id, 1, philo->print);
	pthread_mutex_lock(&philo->fork_right);
	message(philo->s_time, philo->id, 1, philo->print);
	message(philo->s_time, philo->id, 2, philo->print);
	pthread_mutex_lock(&philo->eat);
	philo->time_last_eat = get_time(philo->s_time);
	if (philo->max_eat != 0)
		philo->no_eat++;
	pthread_mutex_unlock(&philo->eat);
	time = get_time(philo->s_time) + philo->time_to_eat;
	while (get_time(philo->s_time) < time)
		usleep(200);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(&philo->fork_right);
}

void	philo_sleep(t_philo *philo)
{
	uint64_t	time;

	message(philo->s_time, philo->id, 3, philo->print);
	time = get_time(philo->s_time) + philo->time_to_sleep;
	while (get_time(philo->s_time) < time)
		usleep(200);
}

int	parsing_arg(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv && argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9' || argv[i][j] == '-')
				return (1);
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[1]) <= 0)
		return (1);
	if (argv[5] && ft_atoi(argv[5]) < 1)
		return (1);
	return (0);
}

int	one_case(int time)
{
	printf("%d 1 died\n", time);
	return (0);
}

int	check_finish(t_philo *philo, int nb)
{
	int	i;
	int	no_eat_tmp;
	int	max_eaten;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_lock(&philo[i].eat);
		no_eat_tmp = philo[i].no_eat;
		max_eaten = philo[i].max_eat;
		pthread_mutex_unlock(&philo[i].eat);
		if (no_eat_tmp != max_eaten)
			return (0);
		i++;
	}
	return (1);
}
