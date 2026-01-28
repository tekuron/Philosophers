/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 23:29:41 by danz              #+#    #+#             */
/*   Updated: 2026/01/27 18:24:05 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define _DEFAULT_SOURCE
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				*dead;
	int				nop;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				notepme;
	int				cur_p;
	long			start_time;
	long			last_time_ate;
	long			times_eaten;
	pthread_t		id;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

int		ft_atoi(const char *nptr);
int		args_init(int argc, char **argv, t_philo **args);
long	get_ms(void);
void	philo_create(t_philo *args);
void	forks(t_philo *args);
void	*philo(void *arg);
int		print_action(t_philo *philo, const char *str);
void	death_check(t_philo	*args);
void	cleanup(t_philo *args);
int		safelock(pthread_mutex_t *dead_lock, pthread_mutex_t *mutex, int *dead);

#endif