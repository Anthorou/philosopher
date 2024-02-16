/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:02:56 by aroussea          #+#    #+#             */
/*   Updated: 2023/09/27 16:06:52 by aroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	create_fork(int *check, pthread_mutex_t *fork)
{
	if (pthread_mutex_init(fork, NULL) != 0)
		*check = 1;
}

t_philo	create_philo(char **argv, int no, int *check)
{
	t_philo	philo;

	create_fork(check, &philo.fork_right);
	create_fork(check, &philo.eat);
	philo.id = no + 1;
	philo.time_to_eat = ft_atoi(argv[3]);
	philo.time_to_sleep = ft_atoi(argv[4]);
	philo.time_last_eat = 0;
	philo.no_eat = 0;
	if (argv[5])
		philo.max_eat = ft_atoi(argv[5]);
	else
		philo.max_eat = -1;
	return (philo);
}

t_philo	*gere_philo(int *check, int nb, char **argv)
{
	t_philo			*philo;
	int				i;
	pthread_mutex_t	*print;

	i = 0;
	print = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	philo = ft_calloc(nb, sizeof(t_philo));
	if (!philo || !print)
		*check = 1;
	if (pthread_mutex_init(print, NULL) != 0)
		*check = 1;
	while (i < nb)
	{
		if (*check != 0)
			return (philo);
		philo[i] = create_philo(argv, i, check);
		philo[i].print = print;
		if (i > 0)
			philo[i].fork_left = &philo[i - 1].fork_right;
		if (nb - i == 1)
			philo[0].fork_left = &philo[i]. fork_right;
		i++;
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	int			check;
	t_philo		*philo;
	uint64_t	s_time;

	check = 0;
	if (argc > 4 && argc < 7)
	{
		if (parsing_arg(argv) != 0)
			return (write(STDERR_FILENO, "Args not valid\n", 15), 1);
		if (ft_atoi(argv[1]) == 1)
			return (one_case(ft_atoi(argv[2])));
		philo = gere_philo(&check, ft_atoi(argv[1]), argv);
		if (check != 0)
			return (end(philo, ft_atoi(argv[1])));
		s_time = get_time(0);
		start(&check, philo, s_time, ft_atoi(argv[1]));
		if (check != 0)
			return (end(philo, ft_atoi(argv[1])));
		return (god(s_time, ft_atoi(argv[2]), philo, ft_atoi(argv[1])));
		return (0);
	}
	else
		write(STDERR_FILENO, "Must have 4 or 5 args\n", 22);
	return (1);
}
