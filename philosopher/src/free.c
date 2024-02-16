/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:41:20 by aroussea          #+#    #+#             */
/*   Updated: 2023/09/28 11:07:00 by aroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	end(t_philo *philo, int nb)
{
	int	i;

	i = 0;
	while (i < nb && philo)
	{
		if (philo[i].tid)
			pthread_detach(philo[i].tid);
		pthread_mutex_destroy(&philo[i].fork_right);
		i++;
	}
	pthread_mutex_destroy(philo[0].print);
	free(philo->print);
	free(philo);
	return (0);
}
