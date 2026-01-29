/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 23:40:02 by danz              #+#    #+#             */
/*   Updated: 2026/01/29 21:42:53 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc > 6 || argc <= 1)
		return (1);
	i = 1;
	j = 0;
	while (i < argc)
	{
		while (argv[i][j])
		{
			if (argv[i][j] > '9' || argv[i][j++] < '0')
				return (1);
		}
		if (ft_atoi(argv[i] <= 0))
			return (1);
		j = 0;
		i++;
	}
	return (0);
}

int	args_init(int argc, char **argv, t_philo *args)
{
	args->start_time = get_ms();
	if (check_args(argc, argv))
		return (-1);
	args->last_time_ate = args->start_time;
	args->times_eaten = 0;
	args->nop = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->notepme = ft_atoi(argv[5]);
	else
		args->notepme = 0;
	return (0);
}

void	philo_create(int *pids, t_philo *args)
{
	int	i;

	i = 0;
	args->fork_sem = sem_open("/fk_z_1", O_CREAT, 0644, args->nop);
	args->print_sem = sem_open("/pt_z_1", O_CREAT, 0644, 1);
	while (i < args->nop)
	{
		pids[i] = fork();
		if (!pids[i])
		{
			if (i % 2)
				usleep((args->time_to_eat / 2) * 1000);
			free(pids);
			args->cur_p = i;
			philo_start(*args);
			return ;
		}
		i++;
	}
}
