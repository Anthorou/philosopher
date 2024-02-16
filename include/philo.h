/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:03:05 by aroussea          #+#    #+#             */
/*   Updated: 2023/09/27 16:20:31 by aroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		tid;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	fork_right;
	pthread_mutex_t	*print;
	pthread_mutex_t	eat;
	uint64_t		s_time;
	int				time_last_eat;
	int				id;
	int				time_to_eat;
	int				time_to_sleep;
	int				no_eat;
	int				max_eat;
}	t_philo;

int			parsing_arg(char **argv);
long		ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
t_philo		create_philo(char **argv, int no, int *check);
int			end(t_philo *philo, int nb);
t_philo		*gere_philo(int *check, int nb, char **argv);
uint64_t	get_time(uint64_t start_time);
void		start(int *check, t_philo *philo, uint64_t s_time, int nb);
int			god(uint64_t s_time, int time_to_die, t_philo *philo, int nb);
void		eat(t_philo *philo);
void		message(uint64_t s_time, int id, int nb, pthread_mutex_t *mutex);
void		philo_sleep(t_philo *philo);
int			one_case(int time);
int			check_finish(t_philo *philo, int nb);

#endif 