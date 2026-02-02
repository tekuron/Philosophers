/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danzamor <danzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:16:35 by danz              #+#    #+#             */
/*   Updated: 2026/02/02 17:59:38 by danzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_for_eos(int *pids, int nop)
{
	int	status;
	int	i;
	int	philos_done;

	philos_done = 0;
	while (philos_done < nop)
	{
		waitpid(-1, &status, 0);
		if (((status >> 8) & 0xFF) != 0)
		{
			i = 0;
			while (i < nop)
			{
				kill(pids[i], SIGKILL);
				i++;
			}
			return ;
		}
		philos_done++;
	}
}

static void	close_philo(t_philo *args)
{
	sem_close(args->eat_sem);
	sem_close(args->fork_sem);
	sem_close(args->print_sem);
	sem_unlink("/fk_z_1");
	sem_unlink("/pt_z_1");
}

void	*monitoring(void *arg)
{
	t_philo	*args;

	args = arg;
	while (1)
	{
		sem_wait(args->eat_sem);
		if (args->notepme && args->times_eaten >= args->notepme)
		{
			sem_post(args->fork_sem);
			sem_post(args->fork_sem);
			close_philo(args);
			exit(0);
		}
		else if (get_ms() - args->last_time_ate >= args->time_to_die)
		{
			sem_wait(args->print_sem);
			printf("%ld %d died\n", get_ms() - args->start_time,
				args->cur_p + 1);
			close_philo(args);
			exit(1);
		}
		sem_post(args->eat_sem);
		usleep(1000);
	}
	return (NULL);
}

static void	routine(t_philo *philo)
{
	if (philo->nop == 1)
	{
		print_action(philo, "has taken a fork\n");
		usleep(philo->time_to_die * 1000);
		return ((void)printf("%ld %d died\n", get_ms() - philo->start_time,
				philo->cur_p + 1));
	}
	while (1)
	{
		sem_wait(philo->fork_sem);
		print_action(philo, "has taken a fork\n");
		sem_wait(philo->fork_sem);
		print_action(philo, "has taken a fork\n");
		sem_wait(philo->eat_sem);
		philo->last_time_ate = get_ms();
		sem_post(philo->eat_sem);
		philo->times_eaten++;
		print_action(philo, "is eating\n");
		usleep(philo->time_to_eat * 1000);
		sem_post(philo->fork_sem);
		sem_post(philo->fork_sem);
		print_action(philo, "is sleeping\n");
		usleep(philo->time_to_sleep * 1000);
		print_action(philo, "is thinking\n");
	}
}

void	philo_start(t_philo args)
{
	char	eat_name[50];

	make_sem_name(eat_name, args.cur_p);
	sem_unlink(eat_name);
	args.eat_sem = sem_open(eat_name, O_CREAT, 0644, 1);
	if (args.eat_sem == SEM_FAILED)
		exit(1);
	sem_unlink(eat_name);
	if (args.nop != 1)
		pthread_create(&args.mon, NULL, monitoring, &args);
	routine(&args);
}
