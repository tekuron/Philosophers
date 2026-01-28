/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 23:22:26 by danz              #+#    #+#             */
/*   Updated: 2026/01/27 22:18:02 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}

void	make_sem_name(char *dst, int id)
{
	char	*id_str;

	id_str = ft_itoa(id);
	if (!id_str)
		return ;
	ft_strlcpy(dst, "/ph_z_", 30);
	ft_strlcat(dst, id_str, 30);
	free(id_str);
}

void	print_action(t_philo *philo, const char *str)
{
	sem_wait(philo->print_sem);
	printf("%li %i", get_ms() - philo->start_time, philo->cur_p + 1);
	printf(" %s", str);
	sem_post(philo->print_sem);
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
