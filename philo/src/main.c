/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 23:16:49 by danz              #+#    #+#             */
/*   Updated: 2026/01/27 22:21:58 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_philo *args)
{
	int	i;

	i = 0;
	while (i < args[0].nop)
	{
		pthread_join(args[i].id, NULL);
		pthread_mutex_destroy(&args[i].eat_lock);
		pthread_mutex_destroy(args[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(args[0].write_lock);
	pthread_mutex_destroy(args[0].dead_lock);
	free(args[0].dead);
	free(args[0].write_lock);
	free(args[0].dead_lock);
	free(args[0].left_fork);
	free(args);
}

int	main(int argc, char **argv)
{
	t_philo		*args;

	if (args_init(argc, argv, &args))
	{
		printf("Usage: philo number_of_philosophers time_to_die time_to_eat");
		printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	philo_create(args);
	death_check(args);
	cleanup(args);
}
