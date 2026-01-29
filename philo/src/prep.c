/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 23:40:02 by danz              #+#    #+#             */
/*   Updated: 2026/01/29 21:42:39 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	forks(t_philo *args)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * args[0].nop);
	while (i < args[0].nop)
	{
		args[i].left_fork = &forks[i];
		args[i].right_fork = &forks[(i + 1) * (i != args[0].nop - 1)];
		pthread_mutex_init(&forks[i], NULL);
		pthread_mutex_init(&args[i].eat_lock, NULL);
		i++;
	}
}

static void	argscpy(t_philo tmp, t_philo *args, int *i)
{
	args[*i].dead = tmp.dead;
	args[*i].start_time = tmp.start_time;
	args[*i].last_time_ate = tmp.start_time;
	args[*i].nop = tmp.nop;
	args[*i].time_to_die = tmp.time_to_die;
	args[*i].time_to_eat = tmp.time_to_eat;
	args[*i].time_to_sleep = tmp.time_to_sleep;
	args[*i].notepme = tmp.notepme;
	args[*i].times_eaten = 0;
	args[*i].write_lock = args[0].write_lock;
	args[*i].dead_lock = args[0].dead_lock;
	args[*i].cur_p = *i;
	(*i)++;
}

int	args_init(int argc, char **argv, t_philo **args)
{
	int		i;
	t_philo	tmp;

	i = 0;
	tmp.start_time = get_ms();
	if (check_args(argc, argv))
		return (-1);
	tmp.nop = ft_atoi(argv[1]);
	tmp.time_to_die = ft_atoi(argv[2]);
	tmp.time_to_eat = ft_atoi(argv[3]);
	tmp.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		tmp.notepme = ft_atoi(argv[5]);
	else
		tmp.notepme = 0;
	tmp.dead = malloc(sizeof(int));
	*(tmp.dead) = 0;
	*args = malloc(tmp.nop * sizeof(t_philo));
	(*args)[0].write_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init((*args)[0].write_lock, NULL);
	(*args)[0].dead_lock = malloc(sizeof(pthread_mutex_t));
	while (i < tmp.nop)
		argscpy(tmp, *args, &i);
	forks(*args);
	return (pthread_mutex_init((*args)[0].dead_lock, NULL), 0);
}

void	philo_create(t_philo *args)
{
	int	i;

	i = 0;
	while (i < args[0].nop)
	{
		pthread_create(&args[i].id, NULL, philo, &args[i]);
		i++;
	}
}
