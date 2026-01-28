/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 23:22:26 by danz              #+#    #+#             */
/*   Updated: 2026/01/27 18:24:00 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safelock(pthread_mutex_t *dead_lock, pthread_mutex_t *mutex, int *dead)
{
	pthread_mutex_lock(dead_lock);
	if (*dead)
		return (pthread_mutex_unlock(dead_lock), 1);
	pthread_mutex_unlock(dead_lock);
	pthread_mutex_lock(mutex);
	pthread_mutex_lock(dead_lock);
	if (*dead)
	{
		pthread_mutex_unlock(mutex);
		pthread_mutex_unlock(dead_lock);
		return (1);
	}
	pthread_mutex_unlock(dead_lock);
	return (0);
}

int	print_action(t_philo *philo, const char *str)
{
	if (safelock(philo->dead_lock, philo->write_lock, philo->dead))
		return (1);
	printf("%li %i", get_ms() - philo->start_time, philo->cur_p + 1);
	printf(" %s", str);
	pthread_mutex_unlock(philo->write_lock);
	return (0);
}

long	get_ms(void)
{
	struct timeval	tv;

	(void)gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_atoi(const char *nptr)
{
	int	ret;
	int	sign;

	ret = 0;
	sign = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		sign++;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		ret *= 10;
		ret += *nptr - '0';
		nptr++;
	}
	if (sign % 2 == 1)
		ret *= -1;
	return (ret);
}
