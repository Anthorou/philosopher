/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:37:23 by aroussea          #+#    #+#             */
/*   Updated: 2023/09/25 14:08:56 by aroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	*ptr;

	i = 0;
	ptr = b;
	if (!b)
		return (b);
	while (i < len)
	{
		*ptr = c;
		ptr++;
		i++;
	}
	return (b);
}

static void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

long	ft_atoi(const char *str)
{
	int		i;
	int		c;
	long	rep;

	rep = 0;
	c = 1;
	i = 0;
	if (!str)
		return (0);
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			c *= -1;
	if (str[i] < 48 || str[i] > 57)
		return (0);
	while ((str[i] >= 48 && str[i] <= 57) && str[i] != '\0')
	{
		rep *= 10;
		rep += str[i] - 48;
		i++;
	}
	return (rep * c);
}

uint64_t	get_time(uint64_t start_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - start_time);
}
