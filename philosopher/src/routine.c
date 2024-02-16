/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:34:31 by aroussea          #+#    #+#             */
/*   Updated: 2023/09/27 16:28:38 by aroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	message(uint64_t s_time, int id, int nb, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%lld %d ", get_time(s_time), id);
	if (nb == 1)
		printf("has taken a fork\n");
	else if (nb == 2)
		printf("is eating\n");
	else if (nb == 3)
		printf("is sleeping\n");
	else if (nb == 4)
		printf("is thinking\n");
	else if (nb == 5)
		printf("died\n");
	if (nb != 5)
		pthread_mutex_unlock(mutex);
}

void	*routine(void *info)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)info;
	i = 0;
	if (philo->id % 2 == 0)
		usleep((philo->time_to_eat * 1000) / 3);
	while (i == 0)
	{
		eat(philo);
		if (philo->max_eat != 0 && (philo->no_eat == philo->max_eat))
			break ;
		philo_sleep(philo);
		message(philo->s_time, philo->id, 4, philo->print);
	}
	return (0);
}

static void	create_thread(t_philo *philo, int *check)
{
	pthread_t	tid;

	if (pthread_create(&tid, NULL, &routine, philo) != 0)
		*check = 1;
	philo->tid = tid;
	return ;
}

void	start(int *check, t_philo *philo, uint64_t s_time, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		philo[i].s_time = s_time;
		create_thread(&philo[i], check);
		if (*check != 0)
			break ;
		i++;
	}
	return ;
}

int	god(uint64_t s_time, int time_to_die, t_philo *philo, int nb)
{
	int	i;
	int	eat_tmp[3];

	i = 0;
	while (i < nb)
	{
		pthread_mutex_lock(&philo[i].eat);
		eat_tmp[0] = philo[i].time_last_eat;
		eat_tmp[1] = philo[i].no_eat;
		eat_tmp[2] = philo[i].max_eat;
		pthread_mutex_unlock(&philo[i].eat);
		if (((get_time(s_time) - eat_tmp[0]) > (uint64_t)time_to_die)
			&& (eat_tmp[1] != eat_tmp[2]))
		{
			message(s_time, philo[i].id, 5, philo[i].print);
			return (end(philo, nb));
		}
		if (eat_tmp[2] != 0 && check_finish(philo, nb) != 0)
			return (end(philo, nb));
		i++;
		if ((nb - i) == 1)
			i = 0;
	}
	return (1);
}
