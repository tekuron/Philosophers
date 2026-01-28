/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 22:12:56 by danz              #+#    #+#             */
/*   Updated: 2026/01/27 18:24:25 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_dead(t_philo *args, int i, int all_done)
{
	pthread_mutex_lock(args[i].dead_lock);
	*(args[i].dead) = 1;
	if (!all_done)
		printf("%li %i has died\n", get_ms() - args[i].start_time, i + 1);
	(void)pthread_mutex_unlock(args[i].dead_lock);
}

void	death_check(t_philo	*args)
{
	int	i;
	int	philos_done;

	i = 0;
	philos_done = 0;
	while (1)
	{
		safelock(args[0].dead_lock, &args[i].eat_lock, args[i].dead);
		if (args[i].notepme && args[i].times_eaten >= args[i].notepme)
			philos_done++;
		else
			philos_done = 0;
		if (get_ms() - args[i].last_time_ate >= args[i].time_to_die
			|| (philos_done == args[0].notepme && args[0].notepme))
		{
			set_dead(args, i, philos_done == args[0].notepme
				&& args[0].notepme);
			pthread_mutex_unlock(&args[i].eat_lock);
			return ;
		}
		pthread_mutex_unlock(&args[i].eat_lock);
		if (++i >= args[0].nop)
			i = 0;
	}
}

int	eat(t_philo *philo)
{
	if (safelock(philo->dead_lock, philo->left_fork, philo->dead))
		return (1);
	print_action(philo, "has taken a fork\n");
	if (safelock(philo->dead_lock, philo->right_fork, philo->dead))
		return (pthread_mutex_unlock(philo->left_fork), 1);
	print_action(philo, "has taken a fork\n");
	if (safelock(philo->dead_lock, &philo->eat_lock, philo->dead))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (pthread_mutex_unlock(philo->right_fork), 1);
	}
	philo->last_time_ate = get_ms();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->eat_lock);
	if (print_action(philo, "is eating\n"))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (pthread_mutex_unlock(philo->right_fork), 1);
	}
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	*philo(void *arg)
{
	t_philo		*philo;

	philo = arg;
	if (philo->cur_p % 2 == 1)
		usleep((philo->time_to_eat / 2) * 1000);
	if (philo->nop == 1)
	{
		print_action(philo, "has taken a fork\n");
		usleep(philo->time_to_die * 1000);
		return (NULL);
	}
	while (1)
	{
		if (eat(philo))
			break ;
		print_action(philo, "is sleeping\n");
		usleep(philo->time_to_sleep * 1000);
		print_action(philo, "is thinking\n");
	}
	return (NULL);
}
