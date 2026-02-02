/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danzamor <danzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 23:29:41 by danz              #+#    #+#             */
/*   Updated: 2026/02/02 17:59:43 by danzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define _DEFAULT_SOURCE
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_philo
{
	int			nop;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			notepme;
	int			cur_p;
	long		start_time;
	long		last_time_ate;
	long		times_eaten;
	sem_t		*eat_sem;
	sem_t		*fork_sem;
	sem_t		*print_sem;
	pthread_t	mon;
}	t_philo;

int		args_init(int argc, char **argv, t_philo *args);
void	philo_create(int *pids, t_philo *args);
void	philo_start(t_philo args);
long	get_ms(void);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	print_action(t_philo *philo, const char *str);
void	make_sem_name(char *dst, int id);
void	wait_for_eos(int *pids, int nop);
size_t	ft_strlen(const char *str);

#endif